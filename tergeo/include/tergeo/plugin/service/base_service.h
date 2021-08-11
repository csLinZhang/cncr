#ifndef _TERGEO_PLUGIN_SERVICE_BASE_SERVICE_H_
#define _TERGEO_PLUGIN_SERVICE_BASE_SERVICE_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"

namespace tergeo {
namespace plugin {
namespace service {
/**
 * @brief tergeo 系统级服务
 */ 
class BaseService : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseService)
    DECLARE_DEFAULT_STRUCTOR(BaseService)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}

    virtual bool process() {return true;}
};
#define REGISTER_SERVICE_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::plugin::service::BaseService, sub_class)
}
}
} // tergeo 
#endif