/**
 * @file topic_observer.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 */
#ifndef _TERGEO_FRAMEWORK_TOPIC_OBSERVER_H
#define _TERGEO_FRAMEWORK_TOPIC_OBSERVER_H
#include "tergeo/framework/topic_holder.h"

namespace tergeo {
namespace framework {
/**
 * @brief 观测最新一帧数据
 */ 
template<typename T>
class TopicObserver : public TopicHolder<T> {
    DECLARE_DEFAULT_STRUCTOR(TopicObserver)
public:    
    /**
     * @brief 获取观测数据
     * @note 与observe函数一起使用
     * @code
     * observer.observe();
     * const T& data = observer.getData();
     * @endcode
     * @see :: observe()
     */ 
    inline
    const T& getData() const {
        return _data_observed;
    }
    /**
     * @brief 观测一帧数据
     */ 
    inline
    void observe() {
        std::lock_guard<std::mutex> lock(TopicHolder<T>::_mutex);
        _data_observed = _data;
    }
    /**
     * @brief 保持当前帧数据 
     */ 
    void proc(const T& data) override {
        std::lock_guard<std::mutex> lock(TopicHolder<T>::_mutex);
        _data = data;
    }
protected:
    T _data, _data_observed;
};
}
}

#endif