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
#ifndef _TERGEO_FRAMEWORK_BASE_MODULE_H_
#define _TERGEO_FRAMEWORK_BASE_MODULE_H_

#include <csignal>
#include <string>
#include "tergeo/common/log.h"
#include "tergeo/common/utils.h"
#include "tergeo/common/status/status.h"

#include "tergeo/core/factory.h"
#include "tergeo/core/application.h"

#include "tergeo/adapter/ros_adapter_manager.h"

namespace tergeo {
namespace framework {
/**
 * @brief 模块基类
 */ 
class BaseModule : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseModule)
    DECLARE_DEFAULT_STRUCTOR(BaseModule)
public:
    /**
     * @brief 初始化函数
     *   - 加载配置文件
     *   - 初始化函数
     * */
    virtual common::Status init() = 0;
    /**
     * @brief 启动模块（多种方式）
     *   - 订阅消息
     *   - 开启定时器
     *   - 启动线程
     * */
    virtual common::Status start() = 0;
    /**
     * @brief 停止模块
     *   - 释放资源
     * */  
    virtual void stop() = 0;
    /**@brief 获取模块名，需要重载 */
    virtual std::string getModuleName() const {return "UnknownModule";}
    /**@brief 获取类型，需要重载 
     * @see 模块类型定义 :: tergeo::ModuleType
    */
    virtual int getModuleType() const {return tergeo::ModuleType::MODULE_UNKNOWN;}
};
#define REGISTER_TERGEO_MODULE_CLASS_CPP(sub_class_name) \
    REGISTER_CLASS_CPP(tergeo::framework::BaseModule, sub_class_name)

}  // namespace 
}

#endif  // 
