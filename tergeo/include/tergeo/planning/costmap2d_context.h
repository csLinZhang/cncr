#ifndef _TERGEO_PLANNING_COSTMAP2D_CONTEXT_H
#define _TERGEO_PLANNING_COSTMAP2D_CONTEXT_H
#include <tergeo/common/status/status.h>
#include "tergeo/planning/costmap2d.h"
#include "tergeo/planning/frame.h"
namespace tergeo {
namespace planning {

class Costmap2DContextPrivate;
class Costmap2DContext {
public:
    Costmap2DContext();
    virtual ~Costmap2DContext();

    common::Status init(const std::string& cfg_file, 
        tergeo::planning::Frame* frame);

    bool updateLocalCostmap(const common::math::Pose2d& current_pose);
    bool updateGlobalCostmap(const common::math::Pose2d& start_pose,
        common::math::Pose2d& end_pose);

    tergeo::planning::Costmap2D* getLocalCostmap() const;
    tergeo::planning::Costmap2D* getGlobalCostmap() const;

private:
    Costmap2DContextPrivate* _ptr = nullptr;    
};

}
}
#endif