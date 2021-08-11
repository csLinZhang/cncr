/**
 * @file topic_adapter.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 封装ros消息，可通过重载进行扩展
 * @details 
 */
#ifndef _TERGEO_ADAPTER_TOPIC_ADAPTER_H_
#define _TERGEO_ADAPTER_TOPIC_ADAPTER_H_
#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <memory>
#include <ros/ros.h>
#include <boost/shared_ptr.hpp>
#include "tergeo/common/time/time.h"
#include "tergeo/common/log.h"
#include "tergeo/common/macro.h"
#include "tergeo/core/factory.h"

namespace tergeo {
namespace adapter {

/// @brief 消息路由基类，继承自Object
class TopicAdapter : public tergeo::core::IPlugin {
    DECLARE_FACTORY(TopicAdapter)
    DECLARE_DEFAULT_STRUCTOR(TopicAdapter)
public: 
    /// @brief 获取消息名，由子类指定
    virtual std::string getTopicName() const = 0;
    
protected:
    /// @brief 初始化
    virtual void initPublisher(ros::NodeHandle* node_handle, int message_history_limit) = 0;
    virtual void initSubscriber(ros::NodeHandle* node_handle, int message_history_limit) = 0;
protected:
    friend class RosAdapterManager;
};

/// @brief 模板类，根据具体消息类型特化模板，实现具体消息路由的扩展
template <typename T>
class TopicTypeAdapter : public TopicAdapter {
    DECLARE_DEFAULT_STRUCTOR(TopicTypeAdapter)
public:
    typedef T DataType;
    typedef boost::shared_ptr<DataType const> DataPtr;

    typedef typename std::function<void(const DataType&)> Callback;

    /**
     * @brief 发布数据，与RosAdapterManager::Publish功能相同
     * @param [in]: 消息实例
     */ 
    inline void publish(const DataType& data) {
        _publisher.publish(data);
    }
    inline bool hasReceived() const {
        return _has_received.load();
    }
    inline double getDelayTime() const {
        std::lock_guard<std::mutex> lock(_time_stamp_lock);
        return (tergeo::common::time::Clock::RosTime() - _lastest_time_stamp).toSec();
    }
protected:    
    void initPublisher(ros::NodeHandle* node_handle, const int message_history_limit) override {
        if (_is_pub_initialized.load()) {
            return;
        }
        _publisher = node_handle->advertise<T>(getTopicName(), message_history_limit, false);                    
        _is_pub_initialized.store(true);
    }
    void initSubscriber(ros::NodeHandle* node_handle, const int message_history_limit) override {
        if (_is_sub_initialized.load()) {
            return;
        }
        _subscriber = node_handle->subscribe(getTopicName(),        
            message_history_limit, &TopicTypeAdapter<T>::procCallback, this);
        _is_sub_initialized.store(true);
    }
    
    inline void procCallback(const DataPtr& msg) {
        {
            std::lock_guard<std::mutex> lock(_time_stamp_lock);
            _lastest_time_stamp = msg->header.stamp;
        }
        _has_received.store(true);
        fireCallbacks(*msg);
    }
    
    inline void fireCallbacks(const DataType& msg) {
        for (auto& callback : _receive_callbacks) {
            callback(msg);
        }   
    }
    
    inline void addCallback(Callback callback) {
        _receive_callbacks.push_back(callback);
    }
private:
    std::vector<Callback> _receive_callbacks;
    
    std::atomic<bool> _is_pub_initialized{false};
    ros::Publisher _publisher;
    std::atomic<bool> _is_sub_initialized{false};
    ros::Subscriber _subscriber;
    
    mutable std::mutex _time_stamp_lock;
    ros::Time _lastest_time_stamp;
    std::atomic<bool> _has_received{false};
    mutable std::mutex _mutex;
    friend class RosAdapterManager;
};

#define REGISTER_TOPIC_ADAPTER_CLASS_CPP(class_name, msg_type, topic_name)          \
    class class_name final :                                                        \
            public tergeo::adapter::TopicTypeAdapter<msg_type> {                    \
        DECLARE_DEFAULT_STRUCTOR(class_name)                                        \
    public:                                                                         \
        std::string getTopicName() const override {                                 \
            return std::string(topic_name);                                         \
        }                                                                           \
    };                                                                              \
    REGISTER_CLASS_CPP(tergeo::adapter::TopicAdapter, class_name)
}
}
#endif