#ifndef _TERGEO_PLUGIN_GUARDIAN_BASE_GUARDIAN_H
#define _TERGEO_PLUGIN_GUARDIAN_BASE_GUARDIAN_H
#include "tergeo/common/common.hpp"
#include "tergeo/adapter/ros_adapter_manager.h"
#include "tergeo/core/factory.h"

#include <ros_msgs/ChassisInfo.h>
#include <ros_msgs/GuardianCommand.h>
namespace tergeo {
namespace plugin {
namespace guardian {

class BaseGuardian : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseGuardian)
    DECLARE_DEFAULT_STRUCTOR(BaseGuardian)
public:    
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    
    virtual bool process(ros_msgs::GuardianCommand& command) = 0;
};
#define REGISTER_GUARDIAN_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::plugin::guardian::BaseGuardian, sub_class)

}
}
}

#endif