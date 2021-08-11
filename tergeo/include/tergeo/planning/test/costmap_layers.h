#ifndef _TERGEO_PLANNING_TEST_COSTMAP_LAYERS_H
#define _TERGEO_PLANNING_TEST_COSTMAP_LAYERS_H
#include "tergeo/planning/costmap2d_layer.h"

namespace tergeo {
namespace planning {
namespace test {

class RectLocalLayer : public tergeo::planning::LocalCostmap2DLayer {
public:
    RectLocalLayer() = default;
    virtual ~RectLocalLayer() = default;
    
    common::Status init() override;
    bool update(const common::math::Pose2d& current_pose) override;
};

class RectGlobalLayer : public tergeo::planning::GlobalCostmap2DLayer {
public:
    RectGlobalLayer() = default;
    virtual ~RectGlobalLayer() = default;
    
    common::Status init() override;
    bool update(const common::math::Pose2d& start_pose,
        const common::math::Pose2d& end_pose) override;
};


}
}
}

#endif