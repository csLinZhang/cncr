/**
 * @file topic_holder.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 */
#ifndef _TERGEO_FRAMEWORK_TOPIC_HOLDER_H
#define _TERGEO_FRAMEWORK_TOPIC_HOLDER_H
#include "tergeo/adapter/ros_adapter_manager.h"

namespace tergeo {
namespace framework {
/**
 * @brief 保持最新一帧数据，该类指在提供一种方便的消息接收与处理方法，避免大量的数据回调 \n
 *        另外通过重载此类，将数据处理逻辑封装在此类中，达到精简主类的效果
 */ 
template<typename T>
class TopicHolder {
    DECLARE_DEFAULT_STRUCTOR(TopicHolder)
public:
    /**
     * @brief 初始化，通过消息名添加回调函数
     * @param [in] topic_name: 消息名
     */ 
    void initHolderAdapter(const std::string topic_name) {
        if (_adapter) {return;}
        _adapter = tergeo::adapter::RosAdapterManager::GetTopicTypeAdapter<T>(topic_name);
        tergeo::adapter::RosAdapterManager::AddTopicCallback(topic_name,
            &TopicHolder<T>::proc, this);
    }
    
    /**
     * @brief 设置时间容忍，达到此时间后，消息默认为过期
     * @param [in] time_tolerance_s: 时间差，单位s
     */ 
    inline void setTimeTolerance(const double time_tolerance_s) {
        _time_tolerance_s = time_tolerance_s;
    }
    
    /// @brief返回延迟时间，单位秒
    inline double getDelayTime() const {
        return _adapter->getDelayTime();
    }

    /// @brief 数据是否已过期
    inline bool isOutDated() const {
        if (_time_tolerance_s <= 1e-3) {
            return false;
        }
        return _adapter->getDelayTime() > _time_tolerance_s;
    }
    inline bool hasReceived() const {
        return _adapter->hasReceived();
    }
    /// @brief 默认回调，需要重载，根据需要上锁
    virtual void proc(const T& data) = 0;
protected:
    mutable std::mutex _mutex;
    double _time_tolerance_s = -1.0;
    tergeo::adapter::TopicTypeAdapter<T>* _adapter = nullptr;
};

}
}

#endif