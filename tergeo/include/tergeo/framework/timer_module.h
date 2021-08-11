/**
 * @file base_module.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 模块接口文件
 * @details tergeo模块的入口接口.\n
 *   所有模块都需要继承此接口，才能通过tergeo_app进行启动.
 */
#ifndef _TERGEO_FRAMEWORK_TIMER_MODULE_H_
#define _TERGEO_FRAMEWORK_TIMER_MODULE_H_

#include "tergeo/framework/base_module.h"
#include "tergeo/adapter/ros_timer.h"

namespace tergeo {
namespace framework {

/**
 * @brief 定时器模块
 */ 
class TimerModule : public tergeo::framework::BaseModule {
    DECLARE_DEFAULT_STRUCTOR(TimerModule)
public:
    /**
     * @brief 设置定时器时间间隔
     * @param [in] period_ms: 单位ms
     */ 
    void setTimerPeriod(const float period_ms);
    /**
     * @brief 启动定时器，可重载
     * @note 重载时，调用 TimerModule::start()
     */ 
    common::Status start() override;
    /**
     * @brief 获取定时器，可添加自定义回调函数
     * @see :: tergeo::adapter::RosTimer
     */ 
    tergeo::adapter::RosTimer* getTimer();
    tergeo::common::CallbackList* getCallbackList();
protected:
    /**
     * @brief 默认回调函数，需要重载，每个执行周期内执行一次
     */ 
    virtual void procOnce() = 0;
protected:
    tergeo::adapter::RosTimer _ros_timer;
};


}  // namespace 
}

#endif  // 
