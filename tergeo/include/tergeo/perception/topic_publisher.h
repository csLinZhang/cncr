#ifndef _TERGEO_PERCEPTION_TOPIC_PUBLISHER_H
#define _TERGEO_PERCEPTION_TOPIC_PUBLISHER_H
#include "tergeo/adapter/ros_adapter_manager.h"
#include "tergeo/adapter/topic_adapter.h"

namespace tergeo {
namespace perception {

template <typename T>
class TopicPublisher {
    DECLARE_DEFAULT_STRUCTOR(TopicPublisher)
public:    
    void initPublisherAdapter() {
        _publisher_adapter = tergeo::adapter::RosAdapterManager::GetTopicTypeAdapter<T>(_publisher_topic_name);
    }
    void publish(const T& data) const {
        //data.header.stamp = tergeo::common::time::Clock::RosTime();
        _publisher_adapter->publish(data);
    }
    void setPublisherTopicName(const std::string& topic_name) {
        _publisher_topic_name = topic_name;
    }
protected:
    std::string _publisher_topic_name;
    tergeo::adapter::TopicTypeAdapter<T>* _publisher_adapter = nullptr;
};


}
}

#endif