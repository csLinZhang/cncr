#ifndef _TERGEO_PLUGIN_PLANNING_BASE_GLOBAL_PLANNER_H
#define _TERGEO_PLUGIN_PLANNING_BASE_GLOBAL_PLANNER_H
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/map/reference_line.h"
namespace tergeo {
namespace planning {

class BaseGlobalPlanner : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseGlobalPlanner)
    DECLARE_DEFAULT_STRUCTOR(BaseGlobalPlanner)
public:    
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    
   virtual bool planOnce(const TCMPose2d& start_pose,
        const TCMPose2d& end_pose,
        const planning::Costmap2D& costmap,
        TCMPose2dVec& reference_line) = 0;
};
#define REGISTER_GLOBAL_PLANNER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::planning::BaseGlobalPlanner, sub_class);
}
}
#endif