#ifndef _TERGEO_PLANNING_BASE_PLANNING_H
#define _TERGEO_PLANNING_BASE_PLANNING_H
#include "tergeo/common/common.hpp"
#include <ros_msgs/PlanningPath.h>
namespace tergeo {
namespace planning {

class BasePlanning : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BasePlanning)
    DECLARE_DEFAULT_STRUCTOR(BasePlanning)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() = 0;
    virtual void stop() = 0;

    virtual bool plan(ros_msgs::PlanningPath &planning_path) = 0;
};
#define REGISTER_PLANNING_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::planning::BasePlanning, sub_class)

}
}
#endif