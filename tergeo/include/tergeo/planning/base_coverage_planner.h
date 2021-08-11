#ifndef _TERGEO_PLUGIN_PLANNING_BASE_COVERAGE_PLANNER_H
#define _TERGEO_PLUGIN_PLANNING_BASE_COVERAGE_PLANNER_H
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"
#include "tergeo/map/reference_line.h"
#include "tergeo/planning/utils.h"

namespace tergeo {
namespace planning {

class BaseCoveragePlanner : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseCoveragePlanner)
    DECLARE_DEFAULT_STRUCTOR(BaseCoveragePlanner)
public:    
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    
   virtual bool planOnce(const common::math::Polyline2d& sweeping_areas,
        TCMPose2dVec& reference_line) = 0;

};
#define REGISTER_COVERAGE_PLANNER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::planning::BaseCoveragePlanner, sub_class)
}
}
#endif