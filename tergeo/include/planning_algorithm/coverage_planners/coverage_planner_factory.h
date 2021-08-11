#ifndef _TERGEO_ALGORITHM_COVERAGE_PLANNER_FACTORY_H_
#define _TERGEO_ALGORITHM_COVERAGE_PLANNER_FACTORY_H_

#include "planning_algorithm/coverage_planners/base_coverage_planner.h"

namespace tergeo{
namespace planning{
namespace algorithm{

class CoveragePlannerFactory{
public:
    CoveragePlannerFactory(){};
    ~CoveragePlannerFactory();
    BaseCoveragePlanner* create(const std::string& factory_cfg);
    BaseCoveragePlanner* create(const std::string& planner_name, const std::string& planner_cfg);
private:
    BaseCoveragePlanner* _instance = nullptr;
};
}
}
}
#endif