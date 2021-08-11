#ifndef _TERGEO_COMMON_CALLBACK_LIST_H
#define _TERGEO_COMMON_CALLBACK_LIST_H
#include <list>
#include <mutex>
#include <functional>
#include "tergeo/common/macro.h"
namespace tergeo {
namespace common {

class CallbackList {
    DECLARE_DEFAULT_STRUCTOR(CallbackList)
public:    
    using Callback = std::function<void()>;
    /// 注意：没有去重操作，必须确保唯一添加！！！！！
    void addCallback(Callback callback) {
        std::lock_guard<std::mutex> lock(_callback_mutex);
        _callbacks.emplace_back(callback);
    }

    template <class T>                                                             
    void addCallback(void (T::*fp)()) {                        
        addCallback(fp);                                         
    }                                                                        
    template <class T>                                                               
    void addCallback(void (T::*fp)(), T *obj) {              
        addCallback(std::bind(fp, obj));  
    }
    
    void fireCallbacks() {
        std::lock_guard<std::mutex> lock(_callback_mutex);
        for (auto& callback : _callbacks) {
            callback();
        }
    }
    void clearCallbacks() {
        std::lock_guard<std::mutex> lock(_callback_mutex);
        _callbacks.clear();
    }

    size_t getCallbackNum() const {
        std::lock_guard<std::mutex> lock(_callback_mutex);
        return _callbacks.size();
    }
    
private:
    mutable std::mutex _callback_mutex;
    std::list<Callback> _callbacks;
};

template <class T>
class CallbackOneList {
    DECLARE_DEFAULT_STRUCTOR(CallbackOneList)
public: 
    using Callback = std::function<void(const T&)>;
    /// 注意：没有去重操作，必须确保唯一添加！！！！！
    void addCallback(Callback callback) {
        std::lock_guard<std::mutex> lock(_callback_mutex);
        _callbacks.emplace_back(callback);
    }

    template <class O>                                                             
    void addCallback(void (O::*fp)(const T&)) {                        
        addCallback(fp);                                         
    }                                                                        
    template <class O>                                                               
    void addCallback(void (O::*fp)(const T&), O *obj) {              
        addCallback(std::bind(fp, obj, std::placeholders::_1));  
    }
    
    void fireCallbacks(const T& data) {
        std::lock_guard<std::mutex> lock(_callback_mutex);
        for (auto& callback : _callbacks) {
            callback(data);
        }
    }
    void clearCallbacks() {
        std::lock_guard<std::mutex> lock(_callback_mutex);
        _callbacks.clear();
    }

    size_t getCallbackNum() const {
        std::lock_guard<std::mutex> lock(_callback_mutex);
        return _callbacks.size();
    }
    
private:
    mutable std::mutex _callback_mutex;
    std::list<Callback> _callbacks;
};

}
}

#endif