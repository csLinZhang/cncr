/**
 * @file ros_timer.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 */
#ifndef _TERGEO_ADAPTER_ROS_TIMER_H_
#define _TERGEO_ADAPTER_ROS_TIMER_H_
#include <ros/ros.h>
#include "tergeo/common/status/status.h"
#include "tergeo/common/callback/callback_list.h"
namespace tergeo {
namespace adapter {
/**
 * @brief ros定时器封装类
 * @details 封装定时器过程，支持多回调函数同时触发
 * @code
 * RosTimer ros_timer;
 * ros_timer.setTimerPeriod(100);
 * ros_timer.addCallback(func);
 * ros_timer.startTimer();
 * @endcode
 */ 
class RosTimer {
    DECLARE_DEFAULT_STRUCTOR(RosTimer)
public:
    /**
     * @brief 设置定时器时间间隔
     * @param [in] period_ms: 时间间隔，单位ms
     */ 
    void setTimerPeriod(float period_ms);
    /**
     * @brief 获取定时器时间间隔
     * @return: 时间间隔，单位ms
     */
    float getTimerPeriod() const;
    
    /**
     * @brief 启动定时器
     */
    common::Status startTimer();

    tergeo::common::CallbackList* getCallbackList();
private:
    void onTimer(const ros::TimerEvent& event);
private:
    ros::Timer _timer;
    float _period_ms = 50;
    tergeo::common::CallbackList _callback_list;
};
}
}
#endif