#ifndef _TERGEO_PLUGIN_VEHICLE_BASE_WRITER_H
#define _TERGEO_PLUGIN_VEHICLE_BASE_WRITER_H

#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"
#include "tergeo/canbus/can_client.h"
#include "tergeo/canbus/can_data_sender.h"

namespace tergeo {
namespace plugin {
namespace vehicle {

class BaseWriter : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseWriter)
    DECLARE_DEFAULT_STRUCTOR(BaseWriter)
public:
    virtual common::Status initialize() = 0;
    virtual common::Status start() = 0;
    virtual void stop() = 0;
    
    void setCanClient(tergeo::canbus::CanClient* can_client) {
        _can_client = can_client;
    }
    void setCanPort(int can_port) {_can_port = can_port;}
    void setTopicName(const std::string& topic_name) {_topic_name = topic_name;}
protected:
    int _can_port = 0;
    std::string _topic_name;
    tergeo::canbus::CanClient* _can_client;
};
#define REGISTER_VEHICLE_WRITER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::plugin::vehicle::BaseWriter, sub_class)

template <typename T>
class CallbackWriter : public tergeo::plugin::vehicle::BaseWriter {
    DECLARE_DEFAULT_STRUCTOR(CallbackWriter)
public:
    common::Status initialize() override;
    common::Status start() override;
    void stop() override;
   
protected:
    virtual common::Status init() = 0;
    virtual void proc(const T& data) = 0;
    
protected:
    std::unique_ptr<tergeo::canbus::CanDataSender> _sender;
};
template <typename T>
common::Status CallbackWriter<T>::initialize() {
    _sender.reset(new tergeo::canbus::CanDataSender());
    common::Status status_init = this->init();
    if (!status_init.isOK()) {
        return status_init;
    }
    _can_client->addCanDataSender(_can_port, _sender.get());
    return common::StatusOK();
}
template <typename T>
common::Status CallbackWriter<T>::start() {
    tergeo::adapter::RosAdapterManager::AddTopicCallback(
        _topic_name, &CallbackWriter<T>::proc, this);
    return common::StatusOK();
}

template <typename T>
void CallbackWriter<T>::stop() {
    // do nothing
}

}
}
} // tergeo 

#endif