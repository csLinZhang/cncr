#ifndef _TERGEO_PLANNING_BASE_LOCAL_PLANNER_H
#define _TERGEO_PLANNING_BASE_LOCAL_PLANNER_H

#include "tergeo/common/common.hpp"
#include "tergeo/planning/costmap2d.h"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"
#include "tergeo/planning/costmap2d.h"
#include "tergeo/planning/utils.h"
namespace tergeo {
namespace planning {

class BaseLocalPlanner : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseLocalPlanner)
    DECLARE_DEFAULT_STRUCTOR(BaseLocalPlanner)
public:    
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    
    virtual bool planOnce(const TCMPose2d& current_pose,
        const VehicleState& vehicle_state,
        const tergeo::planning::Costmap2D& costmap,
        const TCMPose2dVec& reference_line,
        Trajectory &trajectory) = 0;
        
};
#define REGISTER_LOCAL_PLANNER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::planning::BaseLocalPlanner, sub_class)
}
}
#endif