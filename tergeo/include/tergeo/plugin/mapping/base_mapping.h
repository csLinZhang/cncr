#ifndef _TERGEO_PLUGIN_SERVICE_BASE_MAPPING_H_
#define _TERGEO_PLUGIN_SERVICE_BASE_MAPPING_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"

namespace tergeo {
namespace plugin {
namespace mapping {
/**
 * @brief tergeo 系统级服务
 */ 
class BaseMapping : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseMapping)
    DECLARE_DEFAULT_STRUCTOR(BaseMapping)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}

};
#define REGISTER_MAPPING_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::plugin::mapping::BaseMapping, sub_class)
}
}
} // tergeo 
#endif