/**
 * @file notification.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @vesion v1.0
 * @license 核心文件，未经允许，禁止使用
 */
#ifndef _TERGEO_FRAMEWORK_NOTIFICATION_H
#define _TERGEO_FRAMEWORK_NOTIFICATION_H
#include <mutex>
#include <iostream>
#include "tergeo/common/macro.h"
#include "tergeo/common/utils.h"

namespace tergeo {
namespace framework {
/**
 * @brief 跨进程消息通知，任何tergeo模块都可发送与监听
 * @details 单例模式 \n
 *   C格式化字符串形式输出
 * @code 
 *  AINFO_NOTIFY("this is no value");
 *  AINFO_NOTIFY("this is info %d", 1);
 *  AWARN_NOTIFY("this is warn %d", 2);
 *  AERROR_NOTIFY("this is error %d", 3);
 * @endcode
 */ 
class Notification final {
public:
    ~Notification() = default;
    /**
     * @brief 设置类型，一般为模块类型
     * @param [in] type: 模块类型
     * @see :: tergeo::ModuleType
     */ 
    void setType(const int type);
    /**
     * @brief 设置通知是否可用
     * @param [in] enable: 设置是否可用
     * @see :: tergeo::ModuleType
     */ 
    void setEnable(bool enable);

    template<typename... Args>
    void notifyError(const std::string& msg, Args&&... args) {
        if (!_enable) {return;}
        char buf[256] = {0};
        snprintf(buf, sizeof(buf), msg.c_str(), std::forward<Args>(args)...);
        notifyImp(tergeo::NOTIFY_ERROR, std::move(std::string(buf)));
    }
    void notifyError(const std::string& msg) {
        if (!_enable) {return;}
        notifyImp(tergeo::NOTIFY_ERROR, msg);
    }
    template<typename... Args>
    void notifyWarn(const std::string& msg, Args&&... args) {
        if (!_enable) {return;}
        char buf[256] = {0};
        snprintf(buf, sizeof(buf), msg.c_str(), std::forward<Args>(args)...);
        notifyImp(tergeo::NOTIFY_WARN, std::move(std::string(buf)));
    }
    void notifyWarn(const std::string& msg) {
        if (!_enable) {return;}
        notifyImp(tergeo::NOTIFY_WARN, msg);
    }

    template<typename... Args>
    void notifyInfo(const std::string& msg, Args&&... args) {
        if (!_enable) {return;}
        char buf[256] = {0};
        snprintf(buf, sizeof(buf), msg.c_str(), std::forward<Args>(args)...);
        notifyImp(tergeo::NOTIFY_INFO, std::move(std::string(buf)));
    }
    void notifyInfo(const std::string& msg) {
        if (!_enable) {return;}
        notifyImp(tergeo::NOTIFY_INFO, msg);
    }
private:
    void notifyImp(const tergeo::NotifyFlag notify_flag, const std::string& msg);
private:
    int _type = 0;
    bool _enable = true;
    DECLARE_SINGLETON(Notification);
};
}
}
#define AERROR_NOTIFY tergeo::framework::Notification::Instance()->notifyError
#define AWARN_NOTIFY tergeo::framework::Notification::Instance()->notifyWarn
#define AINFO_NOTIFY tergeo::framework::Notification::Instance()->notifyInfo

#endif