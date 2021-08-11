/**
 * @file ros_adapter_manager.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief Ros 消息管理类，全局静态
 */

#ifndef _TERGEO_ADAPTER_ROS_ADAPTER_MANAGER_H_
#define _TERGEO_ADAPTER_ROS_ADAPTER_MANAGER_H_
#include <unordered_map>
#include <mutex>
#include "tergeo/common/status/status.h"
#include "tergeo/adapter/topic_adapter.h"
#include "tergeo/adapter/service_adapter.h"
#include "tergeo/adapter/proto/adapter_config.pb.h"

#include <ros_msgs/Notification.h>

namespace tergeo {
namespace adapter {
/**
 * @brief 消息路由管理类，通过消息名（name），索引消息路由（Adapter
 * @details 单例模式\n
 *   此类封装了Ros中消息机制，相关概念与定义参数参数ros
 *   http://wiki.ros.org/ROS/Tutorials
 */ 
class RosAdapterManager final {
public:
    virtual ~RosAdapterManager() = default;
    /**
     * @brief 初始化函数，由app调用，插件内禁止调用
     */ 
    static bool Init();
    /**
     * @brief 加载.adapter文件，允许被多次调用
     * @param [in] adapter_config_filename: 配置文件名，参考proto定义
     * @return 返回是否加载成功
     */
    static bool Load(const std::string adapter_config_filename);
    
    /**
     * @brief 重置消息，将清除已初始化的消息、服务，慎重调用 
     */ 
    static void Reset();
    
    /**
     * @brief 判断当前类是否已经初始化
     * @return bool
     */ 
    static bool Initialized();

    /**
     * @brief 获取当前NodeHandle句柄，在此类无法满足应用的情况下，可调用此句柄自定义ROS操作
     * @return 返回ros::NodeHandle 句柄
     */ 
    static ros::NodeHandle* GetNodeHandle();
    /**
     * @brief [in] : 创建定时器，以一定的间隔执行
     * @param [in] period_ms: 两次执行的时间间隔，以毫秒为单位，注意不能为负且不能小于1，否则采用默认值：100ms
     * @param [in] callback: 回调函数的地址引用
     * @param [in] obj: 回调函数的类实例
     * @param [in] oneshot: 是否只执行一次，默认为false,循环执行
     * @param [in] autostart: 是否为自动启动，默认为true,自动启动程序
     * @return 返回ros::Timer实例
     */ 
    template <class T>
    static ros::Timer CreateTimer(int period_ms,
                                void (T::*callback)(const ros::TimerEvent &),
                                T *obj, 
                                bool oneshot = false,
                                bool autostart = true) {
        if (period_ms < 1.0) {
            period_ms = 100;
            AWARN << "period less than 1, default 100";            
        }
        return GetNodeHandle()->createTimer(ros::Duration(period_ms * 0.001), 
            callback, obj, oneshot, autostart);
    }
    /**
     * @brief 判断是否存在Topic
     * @param [in] topic_name: 消息（Topic）名，是实际执行类的类名，如LocalizationTopic
     * @return 返回是否存在
     */ 
    static bool HasTopicAdapter(const std::string topic_name);
    /**
     * @brief 根据消息名，获取消息路由的实例，注意：此函数得到的实例是基类，不带消息的类型信息。
     * @param [in] topic_name: 消息名
     * @return 消息路由实例，
     * @note 此实例不要delete，也不要用shared_ptr管理，直接使用即可，其管理权在本类。  
     */ 
    static tergeo::adapter::TopicAdapter* GetTopicAdapter(
            const std::string topic_name);
    /**
     * @brief 根据消息名，获取消息路由的实例，注意：此函数是具体消息对应下的基类，包含消息类型信息。
     * @param [in] topic_name: 消息名
     * @return 消息路由实例，
     * @note 此实例不要delete，也不要用shared_ptr管理，直接使用即可，其管理权在本类。  
     */ 
    template<class T>
    static tergeo::adapter::TopicTypeAdapter<T>* GetTopicTypeAdapter(
            const std::string topic_name) {
        CHECK(!topic_name.empty()) << "Empty topic name";
        tergeo::adapter::TopicAdapter* base_topic = GetTopicAdapter(topic_name);
        CHECK(base_topic) << "No topic adapter, named: " << topic_name;
        tergeo::adapter::TopicTypeAdapter<T>* type_topic = 
            dynamic_cast<tergeo::adapter::TopicTypeAdapter<T>* >(base_topic);
        CHECK(type_topic) << "No topic type adapter, named: " << topic_name;
        return type_topic; 
    }
    /**
     * @brief 发布消息。
     * @param [in] topic_name: 消息名
     * @param [in] msg: 消息实例
     */ 
    template<class T>
    static void Publish(const std::string topic_name, const T& msg) {  
        CHECK(!topic_name.empty()) << "Empty topic name";
        tergeo::adapter::TopicTypeAdapter<T>* topic_adapter = 
            GetTopicTypeAdapter<T>(topic_name);
        CHECK(topic_adapter) << "No topic, named: " << topic_name;
        topic_adapter->publish(msg);                 
    }
    /**
     * @brief 添加消息void调函数
     *        注意：没有去重操作，必须确保唯一添加！！！！！
     * @param [in] topic_name: 消void名
     * @param [in] callback: 回调函数
     */
    template <typename T>                                                                                
    static void AddTopicCallback(const std::string topic_name,
        std::function<void(const T&)> callback) {                                      
        tergeo::adapter::TopicTypeAdapter<T>* topic_adapter = 
            GetTopicTypeAdapter<T>(topic_name);
        CHECK(topic_adapter) << "Null topic, named: " << topic_name;
        topic_adapter->addCallback(callback);       
    } 
    
    /**
     * @brief 添加消息回调函数
     *        注意：没有去重操作，必须确保唯一添加！！！！！
     * @param [in] topic_name: 消息名
     * @param [in] fp: 类函数回调函数
     */
    template <class T, class O>                                                             
    static void AddTopicCallback(const std::string topic_name,             
        void (O::*fp)(const T &data)) {                        
        AddTopicCallback(topic_name, fp);                                         
    } 
    /**
     * @brief 添加消息回调函数
     *        注意：没有去重操作，必须确保唯一添加！！！！！
     * @param [in] topic_name: 消息名
     * @param [in] fp: 类函数回调函数
     * @param [in] obj: 类实例
     */                                                                          
    template <class T, class O>                                                               
    static void AddTopicCallback(const std::string topic_name,              
        void (O::*fp)(const T &data), O *obj) { 
        std::function<void(const T&)> func = 
            std::bind(fp, obj, std::placeholders::_1);              
        AddTopicCallback(topic_name, func);  
    } 
    
    /**
     * @brief 是否有服务路由
     * @param [in] service_name: 服务名
     * @return 返回是否存在
     */   
    static bool HasServiceAdapter(const std::string service_name);
    /**
     * @brief 注册服务函数
     * @param [in] service_name: 服务名
     * @param [in] srv_func: 服务函数
     * @param [in] obj: 类对象实例
     */ 
    template<class T, class MReq, class MRes>
    static void RegeisterService(const std::string service_name, 
            bool(T::*srv_func)(MReq &, MRes &), T *obj) {
        CHECK(HasServiceAdapter(service_name)) << "No service adapter, named:"
            << service_name;
        Instance()->_service_adapter_map[service_name]->_service_server =
            GetNodeHandle()->advertiseService(
            Instance()->_service_adapter_map[service_name]->getServiceName(), 
            srv_func, obj);
    }
    /**
     * @brief 注册服务函数
     * @param [in] service_name: 服务名
     * @param [in] srv_func: 服务函数
     */
    template<class MReq, class MRes>
    static void RegeisterService(const std::string service_name, 
            bool(*srv_func)(MReq&, MRes&)) {
        CHECK(HasServiceAdapter(service_name)) << "No service adapter, named:"
            << service_name;
        Instance()->_service_adapter_map[service_name]->_service_server = 
            GetNodeHandle()->advertiseService(
            Instance()->_service_adapter_map[service_name]->getServiceName(), 
            srv_func);
    }
    /**
     * @brief 获取服务路由
     * @param [in] service_name: 服务名
     * @return 返回服务路由实例，若不存在返回nullptr
     * @note 不要delete或shared_ptr管理，其所有权归本类所有
     */
    static ServiceAdapter* GetServiceAdapter(const std::string service_name);
    /**
     * @brief 获取服务路由，注意带有数据类型的基类实例
     * @param [in]: 服务名
     * @return 返回服务路由实例，若不存在返回nullptr
     * @note 不要delete或shared_ptr管理，其所有权归本类所有
     */
    template<class T>
    static ServiceTypeAdapter<T>* GetServiceTypeAdapter(
            const std::string service_name) {
        ServiceAdapter* base_service = GetServiceAdapter(service_name);
        CHECK(base_service) << "Null service adapter, named: " << service_name;
        ServiceTypeAdapter<T>* type_service = 
            dynamic_cast<ServiceTypeAdapter<T>* >(base_service);
        CHECK(type_service) << "Null service type adapter, named: " 
            << service_name;
        return type_service; 
    }
    /**
     * @brief 发送一条通知
     * @param [in] flag: 消息的标识 @see :: tergeo::NotifyFlag
     * @param [in] type: 消息类型，自定义
     * @param [in] msg: 消息内容
     */
    static void Notify(const int flag, const int type, const std::string& msg);
    
    /**
     * @brief notify stauts error, flag = NOTIFY_STATUS_ERROR  
     */ 
    static void Notify(const common::Status& status);
private:
    bool load(const std::string adapter_filename); 
    bool initDefaultAdapter();
    bool initDefaultService();
    void initTopicAdapter(const std::string name);
    void initServiceAdapter(const std::string name);
    bool hasTopicAdapter(const std::string name);
    bool hasServiceAdapter(const std::string name);
private:
    mutable std::mutex _mutex;
    ros::NodeHandle _node_handle; 
    
    std::unordered_map<std::string, TopicAdapter::Ptr> _topic_adapter_map;
    std::unordered_map<std::string, ServiceAdapter::Ptr> _service_adapter_map;
    
    tergeo::adapter::TopicTypeAdapter<ros_msgs::Notification>* _notification_adapter = nullptr;
    
    std::unordered_map<std::string, proto::TopicAdapterConfig> _topic_adapter_config_map;
    std::unordered_map<std::string, proto::ServiceAdapterConfig> _service_adapter_config_map;

    std::atomic<bool> _initialized{false};
    DECLARE_SINGLETON(RosAdapterManager);
};

}
}
#endif