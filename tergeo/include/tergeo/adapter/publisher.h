/**
 * @file publisher.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 */
#ifndef _TERGEO_ADAPTER_PUBLISHER_H
#define _TERGEO_ADAPTER_PUBLISHER_H
#include "tergeo/adapter/topic_adapter.h"
#include "tergeo/adapter/ros_adapter_manager.h"

namespace tergeo {
namespace adapter {
/**
 * @brief 封装消息发布过程
 */  
template <typename T>
class Publisher {
    DECLARE_DEFAULT_STRUCTOR(Publisher)
public:
    /**
     * @brief 初始化消息发布路由
     * @param [in] topic_name: 消息名
     */ 
    void initPublishAdapter(const std::string topic_name) {
        _adapter = tergeo::adapter::RosAdapterManager::GetTopicTypeAdapter<T>(topic_name);    
    }
    /**
     * @brief 发布消息
     * @param [in] data: 消息实例
     */
    void publish(const T& data) {
        _adapter->publish(data);
    }
private:
    tergeo::adapter::TopicTypeAdapter<T>* _adapter;
};

}
}

#endif