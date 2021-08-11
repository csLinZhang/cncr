#ifndef _SIMULATION_STAGE_ROS_WRAPPER_H_
#define _SIMULATION_STAGE_ROS_WRAPPER_H_

#include <Stage-4.1/stage.hh>
#include <ros/ros.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <rosgraph_msgs/Clock.h>
#include "tf/transform_broadcaster.h"
#include <ros_msgs/ControlCommand.h>

class StageRosWrapper {
public:
  StageRosWrapper(
    int argc, char **argv, bool gui, 
    const char *world_file, bool use_model_names);
  ~StageRosWrapper();

  // Returns 0 on success (both models subscribed), -1 otherwise.
  int SubscribeModels();
  void WorldCallback();
  bool UpdateWorld();

  void controlCmdReceived(
    int idx, const boost::shared_ptr<ros_msgs::ControlCommand const> &msg);

  Stg::World *getWorld() {return _stg_world;}
private:
  //a structure representing a robot in the simulator
  struct StageRobot {
    Stg::ModelPosition *positionmodel;

    std::vector<Stg::ModelRanger *> _laser_models; //multiple lasers
    std::vector<ros::Publisher> laser_pubs;
    
    ros::Publisher pose_gt_pub, chassis_gt_pub, imu_omega_pub;
    ros::Subscriber control_cmd_sub;
  };

private:
  // A helper function that is executed for each stage model.  We use it
  // to search for models of interest.
  static void ghfunc(Stg::Model *mod, StageRosWrapper *node);

  static bool s_update(Stg::World *world, StageRosWrapper *node) {
    node->WorldCallback();
    // We return false to indicate that we want to be called again (an
    // odd convention, but that's the way that Stage works).
    return false;
  }

  void loadConfig(const std::string& tfw);
  void readMapInfo(const std::string& map);
  void addFloorModel();
private:
  Stg::World *_stg_world;
  Stg::Model *_floor;

  ros::NodeHandle _n;
  boost::mutex _msg_lock;

  std::vector<Stg::ModelRanger *> _laser_models;
  std::vector<Stg::ModelPosition *> _position_models;
  std::vector<StageRobot const *> _robot_models;

  ros::Publisher _clock_pub;
  bool _use_model_names;

  ros::Time _base_last_cmd;
  ros::Time _sim_time;
  ros::Time _base_last_globalpos_time;
  ros::Duration _base_watchdog_timeout;
  
  std::vector<Stg::Pose> _base_last_globalpos;

  double _left_top_x;
  double _left_top_y;
  double _resolution;
  double _floor_center_x;
  double _floor_center_y;
  double _wheelbase = -1;
  int _width, _height;

  std::string _map_file_path;
  std::string _tfw_file_path;
  const std::string _tmp_map_path = "/tmp/tmp.jpg";
};

#endif