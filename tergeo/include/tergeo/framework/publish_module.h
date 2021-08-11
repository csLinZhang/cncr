/**
 * @file publish_module.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 模块接口文件
 * @details tergeo模块的入口接口.\n
 *   所有模块都需要继承此接口，才能通过tergeo_app进行启动.
 */
#ifndef _TERGEO_FRAMEWORK_PUBLISH_MODULE_H_
#define _TERGEO_FRAMEWORK_PUBLISH_MODULE_H_

#include "tergeo/framework/timer_module.h"

namespace tergeo {
namespace framework {

/**
 * @brief 定时发布消息模块
 */ 
template <typename T>
class PublishModule : public tergeo::framework::TimerModule {
    DECLARE_DEFAULT_STRUCTOR(PublishModule)
public:
    /** 
     * @brief 初始化发布消息路由
     * @param [in] topic_name: 消息名 
     */
    void initPublishAdapter(const std::string topic_name);
protected:
    /**
     * @brief 更新一帧数据，需要重载
     * @return 返回是否更新成功
     * -- ture 更新成功，定时发送
     * -- false 更新失败，不发送
     */ 
    virtual bool updateData(T& data) = 0;
private:
    /**
     * @brief 定时回调函数
     */ 
    void procOnce() override;
    
private:
    T _publish_data;
    tergeo::adapter::TopicTypeAdapter<T>* _publish_adapter = nullptr;
};
template <typename T>
void PublishModule<T>::initPublishAdapter(const std::string topic_name) {
    _publish_adapter = 
        tergeo::adapter::RosAdapterManager::GetTopicTypeAdapter<T>(topic_name);
}
template <typename T>
void PublishModule<T>::procOnce() {
    if (updateData(_publish_data)) {
        _publish_adapter->publish(_publish_data);
    }
}

}  // namespace 
}

#endif  // 
