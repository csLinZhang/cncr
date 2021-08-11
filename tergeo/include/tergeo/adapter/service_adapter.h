/**
 * @file service_adapter.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @license 核心文件，未经允许，禁止使用
 * @brief 封装ros服务，可通过重载进行扩展
 */
#ifndef _TERGEO_ADAPTER_SERVICE_ADAPTER_H_
#define _TERGEO_ADAPTER_SERVICE_ADAPTER_H_
#include <string>
#include <vector>
#include <mutex>
#include <memory>
#include <atomic>
#include <ros/ros.h>
#include <boost/shared_ptr.hpp>
#include "tergeo/common/time/time.h"
#include "tergeo/common/log.h"
#include "tergeo/common/macro.h"
#include "tergeo/core/factory.h"
namespace tergeo {
namespace adapter {

/// @brief 服务路由的基类
class ServiceAdapter : public tergeo::core::IPlugin {
    DECLARE_FACTORY(ServiceAdapter)
    DECLARE_DEFAULT_STRUCTOR(ServiceAdapter)
public:    
    /// @brief 获取服务名，由子类指定
    virtual std::string getServiceName() const = 0;
    
    /// @brief 是否存在该服务 
    virtual bool isExist() = 0;
    /// @brief 服务是否有效
    virtual bool isValid() = 0;
    /// @brief 初始化
    virtual void initServiceClient(ros::NodeHandle* node_handle) = 0;
    
protected:
    ros::ServiceServer _service_server;
    std::atomic<bool> _is_client_initialized{false};
    ros::ServiceClient _service_client;
    friend class RosAdapterManager;
};

/// @brief 模板类，根据具体服务类型特化模板，实现具体服务路由的扩展
template <typename T>
class ServiceTypeAdapter : public ServiceAdapter {
    DECLARE_DEFAULT_STRUCTOR(ServiceTypeAdapter)
public:
    typedef typename T::Request Request;
    typedef typename T::Response Response;  

    /// @brief 是否存在该服务
    bool isExist() override {
        return _service_client.exists();
    }
    /// @brief 服务是否有效
    bool isValid() override {
        return _service_client.isValid();
    }
    
    /// @brief 初始化
    void initServiceClient(ros::NodeHandle* node_handle) override {
        if (_is_client_initialized.load()) {
            return;
        }
        _service_client = node_handle->serviceClient<T>(getServiceName());
        _is_client_initialized.store(true);
    }

    /**
     * @brief 服务请求
     * @param [in]: 请求
     * @param [out]: 回应
     * @return 返回是否请求成功
     */ 
    bool call(Request& request, Response& response) {
        if (!isExist() || !isValid()) {
            return false;
        } else {
            return _service_client.call(request, response);
        }
    }
     /**
     * @brief 服务请求
     * @param [in/out] 请求与回应
     * @return 返回是否请求成功
     */ 
    bool call(T& service) {
        if (!isExist() || !isValid()) {
            return false;
        } else {
            return _service_client.call(service);
        }
    }
};
#define REGISTER_SERVICE_ADAPTER_CLASS_CPP(class_name, msg_type, service_name)  \
    class class_name final :                                                    \
            public tergeo::adapter::ServiceTypeAdapter<msg_type> {              \
        DECLARE_DEFAULT_STRUCTOR(class_name)                                    \
    public:                                                                     \
        std::string getServiceName() const override {                           \
            return std::string(service_name);                                   \
        }                                                                       \
    };                                                                          \
    REGISTER_CLASS_CPP(tergeo::adapter::ServiceAdapter, class_name)

}
}
#endif