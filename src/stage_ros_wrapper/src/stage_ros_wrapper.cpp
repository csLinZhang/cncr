#include <fstream>
#include <iostream>
#include <arpa/inet.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

#include "stage_ros_wrapper.h"
#include <ros_msgs/Odometry.h>
#include <ros_msgs/ChassisInfo.h>
#include <sensor_msgs/PointCloud.h>
#include <ros_msgs/PerceptionObstacles.h>
#include <sensor_msgs/Imu.h>
#include <iostream>
StageRosWrapper::StageRosWrapper(int argc, char **argv, bool gui, 
                                const char *world_file, 
                                bool use_model_names) {
  this->_use_model_names = use_model_names;
  this->_sim_time.fromSec(0.0);
  this->_base_last_cmd.fromSec(0.0);
  double t = 0.2;
  this->_base_watchdog_timeout.fromSec(t);
  
  ros::NodeHandle localn("~");
  
  std::string data_path="", map="", tfw="";
  if(!localn.getParam("data_path", data_path)){
    ROS_FATAL("The data_path must be set!");
  }
  if(!localn.getParam("map", map)){
    ROS_FATAL("The map must be set!");
  }
  if(!localn.getParam("tfw", tfw)){
    ROS_FATAL("The tfw must be set!");
  }
  _map_file_path = data_path + "/" + map;
  _tfw_file_path = data_path + "/" + tfw;
  std::cout << "The map file path is: " << _map_file_path << std::endl;
  std::cout << "The tfw file path is: " << _tfw_file_path << std::endl;
  loadConfig(_tfw_file_path);
  readMapInfo(_map_file_path);
  
  // check the existence of the world file.
  struct stat s;
  if (stat(world_file, &s) != 0) {
    ROS_FATAL("The world file %s does not exist.", world_file);
    ROS_BREAK();
  }

  // initialize libstage
  Stg::Init(&argc, &argv);
  if (gui){
    this->_stg_world = new Stg::WorldGui(600, 400, "Stage (ROS)");
  }else{
    this->_stg_world = new Stg::World();
  }
    
  addFloorModel();
  this->_stg_world->Load(world_file);

  // avoid our callback being invoked before we're ready.
  this->_stg_world->AddUpdateCallback((Stg::world_callback_t) s_update, this);
  this->_stg_world->ForEachDescendant((Stg::model_callback_t) ghfunc, this);
}

StageRosWrapper::~StageRosWrapper() {
  for (std::vector<StageRobot const *>::iterator r = this->_robot_models.begin();
       r != this->_robot_models.end(); ++r) {
    delete *r;
  }
  if(_floor){
    delete _floor;
    _floor = NULL;
  }
  if(_stg_world){
    delete _stg_world;
    _stg_world = NULL;
  }
}

void StageRosWrapper::loadConfig(const std::string& tfw){
  std::ifstream infile(tfw.c_str());
  if(!infile.is_open()){
    ROS_FATAL("open tfw file failed!");
    std::cerr << tfw <<std::endl;
    return;
  }
  double _geo_transform[6];
  infile >> _geo_transform[0] >> _geo_transform[1] >> _geo_transform[2]
         >> _geo_transform[3] >> _geo_transform[4] >> _geo_transform[5];
  infile.close();
  _resolution = std::abs(_geo_transform[0]);
  _left_top_x = _geo_transform[4];
  _left_top_y = _geo_transform[5];
  std::cout<<_left_top_x<<","<<_left_top_y<<"\n";
}

void StageRosWrapper::readMapInfo(const std::string& map){
  cv::Mat img = cv::imread(map,CV_LOAD_IMAGE_GRAYSCALE);
  if(img.empty()){
    ROS_FATAL("open map file failed!");
    std::cerr << map <<std::endl;
    return;
  }
  for(int r = 0; r < img.rows; ++r){
    for(int c = 0; c < img.cols; ++c){
      img.at<uchar>(r, c) = img.at<uchar>(r, c) < 200 ? 0 : 255;
    }
  }
  cv::imwrite(_tmp_map_path, img);
  // todo: find out why some images(png format) has an coodinate offset.
  // std::string prefix = _map_file_path.substr(_map_file_path.find_last_of("."));
  _width = img.cols;
  _height = img.rows;

  std::cout<<"original image h and w is "<<_height<<","<<_width<<"\n";
}

void StageRosWrapper::addFloorModel(){
  _floor = new Stg::Model(_stg_world, NULL, "model", "floor");
  double centerx = _left_top_x + 0.5 * _width * _resolution;
  double centery = _left_top_y - 0.5 * _height * _resolution;
  _floor_center_x = centerx;
  _floor_center_y = centery;
  Stg::Pose pose(0,0,0,0); 
  Stg::Size size(_width*_resolution, _height*_resolution, 2.0);
  Stg::Geom g(pose, size);
  _floor->SetGeom(g);
  // 室外坐标过大时,显示失效,改为向外发布消息时加上偏置_floor_center_x,_floor_center_y
  // _floor->SetPose(Stg::Pose(centerx, centery, 0, 0));// floor model's center in the world
  _floor->SetPose(Stg::Pose(0, 0, 0, 0));// floor model's center in the world
  _floor->SetColor(Stg::Color(0, 0, 0, 0.8));
  _floor->LoadBitmap(_tmp_map_path);//_map_file_path
  _floor->SetBoundary(true);
  _floor->SetGuiMove(false);
  _floor->SetGuiOutline(true);
  _stg_world->AddModel(_floor);
}

void StageRosWrapper::ghfunc(Stg::Model *mod, StageRosWrapper *node) {
  if (dynamic_cast<Stg::ModelRanger *>(mod))
    node->_laser_models.push_back(dynamic_cast<Stg::ModelRanger *>(mod));
  if (dynamic_cast<Stg::ModelPosition *>(mod)) {
    Stg::ModelPosition *p = dynamic_cast<Stg::ModelPosition *>(mod);
    // remember initial poses
    node->_position_models.push_back(p);
  }
}

void StageRosWrapper::controlCmdReceived(
    int idx, const boost::shared_ptr<ros_msgs::ControlCommand const> &msg) {
  boost::mutex::scoped_lock lock(_msg_lock);  
  if(abs(msg->speed_mps)<1e-3){
    this->_position_models[idx]->SetSpeed(0, 0, 0);
  }else{
    double steer = std::atan(msg->omega_radps*_wheelbase / msg->speed_mps);
    this->_position_models[idx]->SetSpeed(msg->speed_mps, 0, steer);
  }
  this->_base_last_cmd = this->_sim_time;
}

int StageRosWrapper::SubscribeModels() {
  _n.setParam("/use_sim_time", true);

  const int r = 0; //robot model index
  StageRobot *new_robot = new StageRobot;
  new_robot->positionmodel = this->_position_models[r];
  new_robot->positionmodel->Subscribe();

  for (size_t s = 0; s < this->_laser_models.size(); s++) {
    if (this->_laser_models[s] and this->_laser_models[s]->Parent() == 
        new_robot->positionmodel) {
      new_robot->_laser_models.push_back(this->_laser_models[s]);
      this->_laser_models[s]->Subscribe();
    }
  }
  
  new_robot->pose_gt_pub = _n.advertise<ros_msgs::Odometry>(
    "/tergeo/localization/pose", 10);
  new_robot->chassis_gt_pub = _n.advertise<ros_msgs::ChassisInfo>(
    "/tergeo/vehicle/chassis/info", 10);
  new_robot->imu_omega_pub = _n.advertise<sensor_msgs::Imu>(
    "/sensor/imu/center/pose", 10);

  
  new_robot->control_cmd_sub = _n.subscribe<ros_msgs::ControlCommand>(
    "/tergeo/control/command",10, 
    boost::bind(&StageRosWrapper::controlCmdReceived, this, r, _1));

  for (size_t s = 0; s < new_robot->_laser_models.size(); ++s) {
    if (new_robot->_laser_models.size() == 1){
      new_robot->laser_pubs.push_back(_n.advertise<ros_msgs::PerceptionObstacles>(
          "/tergeo/perception/obstacles", 10));
    }else{
      // TODO
    }
  }
  this->_robot_models.push_back(new_robot);
  _clock_pub = _n.advertise<rosgraph_msgs::Clock>("/clock", 10);

  return 0;
}

bool StageRosWrapper::UpdateWorld() {
  return this->_stg_world->UpdateAll();
}

void StageRosWrapper::WorldCallback() {
  boost::mutex::scoped_lock lock(_msg_lock);

  this->_sim_time.fromSec(_stg_world->SimTimeNow() / 1e6);
  // We're not allowed to publish clock==0, because it used as a special
  // value in parts of ROS, #4027.
  if (this->_sim_time.sec == 0 && this->_sim_time.nsec == 0) {
    ROS_DEBUG("Skipping initial simulation step, to avoid publishing clock==0");
    return;
  }

  // TODO make this only affect one robot if necessary
  if ((this->_base_watchdog_timeout.toSec() > 0.0) &&
      ((this->_sim_time - this->_base_last_cmd) >= this->_base_watchdog_timeout)) {
    for (size_t r = 0; r < this->_position_models.size(); r++)
      this->_position_models[r]->SetSpeed(0.0, 0.0, 0.0);
  }

  //loop on the robot models
  for (size_t r = 0; r < this->_robot_models.size(); ++r) {
    if (r != 0) { // only deal with robot0 as others are obstacles.
      break;
    }

    StageRobot const *robotmodel = this->_robot_models[r];
    if(_wheelbase<0){
      _wheelbase = robotmodel->positionmodel->GetWheelbase();
    }
    
    //loop on the laser devices for the current robot
    for (size_t s = 0; s < robotmodel->_laser_models.size(); ++s) {
      Stg::ModelRanger const *lasermodel = robotmodel->_laser_models[s];
      const std::vector<Stg::ModelRanger::Sensor> &sensors = 
        lasermodel->GetSensors();

      if (sensors.size() > 1)
        ROS_WARN("ROS Stage currently supports rangers with 1 sensor only.");

      // for now we access only the zeroth sensor of the ranger - good
      // enough for most laser models that have a single beam origin
      const Stg::ModelRanger::Sensor &sensor = sensors[0];
      double offsetx = robotmodel->positionmodel->GetGeom().size.x / 2 
                     + std::abs(robotmodel->positionmodel->GetGeom().pose.x);
      
      if (sensor.ranges.size()) {
        ros_msgs::PerceptionObstacles msg;
        ros_msgs::PerceptionObstacleItem item;
        ros_msgs::Vector3f pt;
        double angle_min = -sensor.fov / 2.0;
        double angle_max = +sensor.fov / 2.0;
        double angle_increment = sensor.fov / (double) (sensor.sample_count - 1);
        double range_min = sensor.range.min;
        double range_max = sensor.range.max;
        for (unsigned int i = 0; i < sensor.ranges.size(); i++) {
          double rad = angle_min + i * angle_increment;
          pt.x = sensor.ranges[i]*std::cos(rad) + offsetx;
          pt.y = sensor.ranges[i]*std::sin(rad); //sensor.pose.y
          pt.z = 1.0;
          item.points.push_back(pt);
        }
        msg.obstacle_list.push_back(item);
        msg.header.stamp = ros::Time::now();
        robotmodel->laser_pubs[s].publish(msg);
      }
    }


    // Also publish the ground truth pose and velocity
    Stg::Pose gpose = robotmodel->positionmodel->GetGlobalPose();
    tf::Quaternion q_gpose;
    q_gpose.setRPY(0.0, 0.0, gpose.a);
    
    tf::Transform gt(q_gpose, tf::Point(gpose.x, gpose.y, 0.0));
    // Velocity is 0 by default and will be set only 
    // if there is previous pose and time delta>0
    Stg::Velocity gvel(0, 0, 0, 0);
    if (this->_base_last_globalpos.size() > r) {
      Stg::Pose prevpose = this->_base_last_globalpos.at(r);
      double dT = (this->_sim_time - this->_base_last_globalpos_time).toSec();
      if (dT > 0)
        gvel = Stg::Velocity(
            (gpose.x - prevpose.x) / dT,
            (gpose.y - prevpose.y) / dT,
            (gpose.z - prevpose.z) / dT,
            Stg::normalize(gpose.a - prevpose.a) / dT
        );
      this->_base_last_globalpos.at(r) = gpose;
    } else //There are no previous readings, adding current pose...
      this->_base_last_globalpos.push_back(gpose);

    // 注:stage所定的位置是中心点在世界坐标系下的坐标,因此要根据配置转换到车辆定位中心
    ros_msgs::Odometry pose_gt_msg;
    pose_gt_msg.header.stamp = ros::Time::now();
    
    pose_gt_msg.pose.position.x = gt.getOrigin().x() + _floor_center_x;
    pose_gt_msg.pose.position.y = gt.getOrigin().y() + _floor_center_y;
    
    pose_gt_msg.pose.position.z = 0;
    pose_gt_msg.pose.orientation.x = gt.getRotation().x();
    pose_gt_msg.pose.orientation.y = gt.getRotation().y();
    pose_gt_msg.pose.orientation.z = gt.getRotation().z();
    pose_gt_msg.pose.orientation.w = gt.getRotation().w();

    robotmodel->pose_gt_pub.publish(pose_gt_msg);

    ros_msgs::ChassisInfo chassis_gt_msg;
    Stg::Velocity v = robotmodel->positionmodel->GetVelocity();
    chassis_gt_msg.header.stamp = ros::Time::now();
    chassis_gt_msg.speed_mps = v.x;
    chassis_gt_msg.omega_radps = v.x * std::tan(v.a);
    robotmodel->chassis_gt_pub.publish(chassis_gt_msg);

    sensor_msgs::Imu imu_msg;
    imu_msg.header.stamp = chassis_gt_msg.header.stamp;
    imu_msg.angular_velocity.x = 0;
    imu_msg.angular_velocity.y = 0;
    imu_msg.angular_velocity.z = chassis_gt_msg.omega_radps;
    robotmodel->imu_omega_pub.publish(imu_msg);
  }

  this->_base_last_globalpos_time = ros::Time::now();
  rosgraph_msgs::Clock clock_msg;
  clock_msg.clock = _sim_time;
  this->_clock_pub.publish(clock_msg);
}