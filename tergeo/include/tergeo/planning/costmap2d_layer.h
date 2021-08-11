#ifndef _TERGEO_PLANNING_COSTMAP2D_LAYER_H
#define _TERGEO_PLANNING_COSTMAP2D_LAYER_H

#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/planning/costmap2d.h"
#include "tergeo/planning/frame.h"

namespace tergeo {
namespace planning {

class Layer : public tergeo::core::IPlugin {
public:
    Layer() = default;
    virtual ~Layer() = default;
    virtual common::Status init() = 0;

    void setCostmap(tergeo::planning::Costmap2D* costmap) {
        _costmap = costmap;
    }
    void setFrame(tergeo::planning::Frame* frame) {
        _frame = frame;
    }
protected:
    tergeo::planning::Costmap2D* _costmap = nullptr;
    tergeo::planning::Frame* _frame = nullptr;
};

class LocalCostmap2DLayer : public Layer {
    DECLARE_FACTORY(LocalCostmap2DLayer)
    DECLARE_DEFAULT_STRUCTOR(LocalCostmap2DLayer)
public:    
    virtual bool update(const common::math::Pose2d& current_pose) = 0;
};
#define REGISTER_LOCAL_COSTMAP2D_LAYER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::planning::LocalCostmap2DLayer, sub_class)

class GlobalCostmap2DLayer : public Layer {
    DECLARE_FACTORY(GlobalCostmap2DLayer)
    DECLARE_DEFAULT_STRUCTOR(GlobalCostmap2DLayer)
public:    
    virtual bool update(const common::math::Pose2d& start_pose,
        const common::math::Pose2d& end_pose) = 0;
};
#define REGISTER_GLOBAL_COSTMAP2D_LAYER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::planning::GlobalCostmap2DLayer, sub_class)

}
}
#endif