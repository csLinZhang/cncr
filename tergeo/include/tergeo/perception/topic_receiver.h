#ifndef _TERGEO_PERCEPTION_TOPIC_RECEIVER_H
#define _TERGEO_PERCEPTION_TOPIC_RECEIVER_H
#include "tergeo/adapter/ros_adapter_manager.h"
#include "tergeo/adapter/topic_adapter.h"
#include "tergeo/common/thread/thread_pool.h"

namespace tergeo {
namespace perception {

template <typename T>
class TopicReceiver {
    DECLARE_DEFAULT_STRUCTOR(TopicReceiver)
protected:
    void initReceiverAdapter() {
        tergeo::adapter::RosAdapterManager::AddTopicCallback(_receiver_topic_name,
            &TopicReceiver<T>::onCallback, this);
    }
    void setReceiverTopicName(const std::string& topic_name) {
        _receiver_topic_name = topic_name;
    }
    virtual void proc(const T& data) = 0;
private:
    void onCallback(const T& data) {
        tergeo::common::ThreadPool::Instance()->schedule(std::bind(&TopicReceiver<T>::proc, this, data));
    }
protected:
    std::string _receiver_topic_name;
};

}
}

#endif
