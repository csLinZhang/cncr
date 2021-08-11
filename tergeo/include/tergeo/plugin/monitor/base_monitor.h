#ifndef _TERGEO_PLUGIN_MONITOR_BASE_MONITOR_H_
#define _TERGEO_PLUGIN_MONITOR_BASE_MONITOR_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"

namespace tergeo {
namespace plugin {
namespace monitor {

class BaseMonitor : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseMonitor)
    DECLARE_DEFAULT_STRUCTOR(BaseMonitor)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    /**
     * @brief return false will be ignored
     */ 
    virtual bool process(std::string& message, uint8_t& level, int& error_code) = 0;
};
#define REGISTER_MONITOR_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::plugin::monitor::BaseMonitor, sub_class)
}
}
} // tergeo 
#endif