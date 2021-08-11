#include "stage_ros_wrapper.h"

int main(int argc, char** argv) { 
    if( argc < 2 ) {
        std::cout << "Please input worldfile." << std::endl;
        exit(-1);
    }

    ros::init(argc, argv, "stageros");
    bool gui = true;
    bool use_model_names = false;
    for(int i=0;i<(argc-1);i++) {
        if(!strcmp(argv[i], "-g")) {
            gui = false;
        }
        if(!strcmp(argv[i], "-u")) {
            use_model_names = true;
        }
    }
    StageRosWrapper sn(argc-1, argv, gui, argv[argc-1], use_model_names);
    if(sn.SubscribeModels() != 0) {
        exit(-1);
    }
    boost::thread t = boost::thread(boost::bind(&ros::spin));
    sn.getWorld()->Start();
    // TODO: get rid of this fixed-duration sleep, using some Stage builtin
    // PauseUntilNextUpdate() functionality.
    ros::WallRate r(10.0);
    while(ros::ok() && !sn.getWorld()->TestQuit()) {
        if(gui) {
            Fl::wait(r.expectedCycleTime().toSec());
        }else {
            sn.UpdateWorld();
            r.sleep();
        }
    }
    t.join();

    exit(0);
}