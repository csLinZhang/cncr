#ifndef _TERGEO_PLUGIN_PREDICTION_BASE_EVALUATOR_H
#define _TERGEO_PLUGIN_PREDICTION_BASE_EVALUATOR_H
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/prediction/obstacle_queue.h"
namespace tergeo {
namespace prediction {

class BaseEvaluator : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseEvaluator)
    DECLARE_DEFAULT_STRUCTOR(BaseEvaluator)
public:    
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    /**
     * @brief 状态、意图、速度
     */ 
    virtual bool evaluate(const double current_stamp, 
        const Eigen::Matrix4d& current_pose,
        ObstacleQueue* obstacle_queue) = 0;
};
#define REGISTER_PREDICTION_EVALUATOR_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::prediction::BaseEvaluator, sub_class);
}
}
#endif