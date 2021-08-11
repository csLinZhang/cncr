#ifndef _TERGEO_PLUGIN_SERVICE_BASE_DRIVER_H_
#define _TERGEO_PLUGIN_SERVICE_BASE_DRIVER_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"

namespace tergeo {
namespace plugin {
namespace driver {
/**
 * @brief tergeo 系统级服务
 */ 
class BaseDriver : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseDriver)
    DECLARE_DEFAULT_STRUCTOR(BaseDriver)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}

};
#define REGISTER_DRIVER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::plugin::driver::BaseDriver, sub_class)
}
}
} // tergeo 
#endif