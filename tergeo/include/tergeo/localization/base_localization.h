#ifndef _TERGEO_LOCALIZATION_BASE_LOCALIZATION_H_
#define _TERGEO_LOCALIZATION_BASE_LOCALIZATION_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"
#include <tf2_ros/transform_broadcaster.h>
#include <ros_msgs/Odometry.h>

namespace tergeo {
namespace localization {

class BaseLocalization : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseLocalization)
    DECLARE_DEFAULT_STRUCTOR(BaseLocalization)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}

    virtual bool process(ros_msgs::Odometry& odometry) = 0;
};
#define REGISTER_LOCALIZATION_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::localization::BaseLocalization, sub_class)
}
} // tergeo 
#endif