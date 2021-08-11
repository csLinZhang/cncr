#ifndef _TERGEO_PLUGIN_PREDICTION_BASE_PREDICTOR_H
#define _TERGEO_PLUGIN_PREDICTION_BASE_PREDICTOR_H
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/prediction/obstacle_container.h"
namespace tergeo {
namespace prediction {

class BasePredictor : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BasePredictor)
    DECLARE_DEFAULT_STRUCTOR(BasePredictor)
public:    
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    
    virtual bool predict(const double current_stamp, 
        const Eigen::Matrix4d& current_pose,
        ObstacleQueue* obstacle_queue) = 0;
};
#define REGISTER_PREDICTION_PREDICTOR_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::prediction::BasePredictor, sub_class);
}
}
#endif