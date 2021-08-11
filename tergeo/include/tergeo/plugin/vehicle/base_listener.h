#ifndef _TERGEO_PLUGIN_VEHICLE_BASE_LISTENER_H_
#define _TERGEO_PLUGIN_VEHICLE_BASE_LISTENER_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/adapter/ros_adapter_manager.h"
#include "tergeo/canbus/can_client.h"
#include "tergeo/canbus/can_data_receiver.h"

namespace tergeo {
namespace plugin {
namespace vehicle {

class BaseListener : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseListener)
    DECLARE_DEFAULT_STRUCTOR(BaseListener)
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
#define REGISTER_VEHICLE_LISTENER_CLASS_CPP(sub_listener) \
    REGISTER_CLASS_CPP(tergeo::plugin::vehicle::BaseListener, sub_listener)

template <typename T>
class TimerListener : public tergeo::plugin::vehicle::BaseListener {
    DECLARE_DEFAULT_STRUCTOR(TimerListener)
public:
    common::Status initialize() override;
    common::Status start() override;
    void stop() override;
   
protected:
    // set: topic_name, frequency, can_port
    virtual common::Status init() = 0;
    void publish();
protected:
    T _publish_data;
    tergeo::adapter::TopicTypeAdapter<T>* _publish_adapter;
    std::unique_ptr<tergeo::canbus::CanDataReceiver<T> > _receiver;
};
template <typename T>
common::Status TimerListener<T>::initialize() {
    _receiver.reset(new tergeo::canbus::CanDataReceiver<T>());
    common::Status status_init = this->init();
    if (!status_init.isOK()) {
        return status_init;
    }
    _publish_adapter = tergeo::adapter::RosAdapterManager::GetTopicTypeAdapter<T>(_topic_name);    
    _can_client->addCanDataReceiver(_can_port, _receiver.get());
    return common::StatusOK();
}
template <typename T>
common::Status TimerListener<T>::start() {
    _receiver->start();
    _receiver->getThread()->addCallback(&TimerListener<T>::publish, this);
    return common::StatusOK();
}

template <typename T>
void TimerListener<T>::stop() {
    _receiver->stop();
}

template <typename T>
void TimerListener<T>::publish() {
    _receiver->getRecvData(_publish_data);
    _publish_data.header.stamp = tergeo::common::time::Clock::RosTime();
    _publish_adapter->publish(_publish_data);
}

}
}
} // tergeo 
#endif