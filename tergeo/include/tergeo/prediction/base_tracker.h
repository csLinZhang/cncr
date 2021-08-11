#ifndef _TERGEO_PLUGIN_PREDICTION_BASE_TRACKER_H
#define _TERGEO_PLUGIN_PREDICTION_BASE_TRACKER_H
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/prediction/obstacle_container.h"
namespace tergeo {
namespace prediction {

class BaseTracker : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseTracker)
    DECLARE_DEFAULT_STRUCTOR(BaseTracker)
public:    
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    
    virtual bool track(const std::vector<tergeo::prediction::Obstacle>& obstacles,
       ObstacleContainer* obstacle_container) = 0;
};
#define REGISTER_PREDICTION_TRACKER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::prediction::BaseTracker, sub_class);
}
}
#endif