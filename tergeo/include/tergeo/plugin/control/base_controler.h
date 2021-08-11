#ifndef _TERGEO_PLUGIN_CONTROL_BASE_CONTROLER_H
#define _TERGEO_PLUGIN_CONTROL_BASE_CONTROLER_H

#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"

#include <ros_msgs/ControlCommand.h>
namespace tergeo {
namespace plugin {
namespace control {

class BaseControler : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseControler)
    DECLARE_DEFAULT_STRUCTOR(BaseControler)
public:    
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    
    virtual bool process(ros_msgs::ControlCommand& control_command) = 0;
};

#define REGISTER_CONTROLER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::plugin::control::BaseControler, sub_class)

}
}
}

#endif