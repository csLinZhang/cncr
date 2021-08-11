#ifndef _TERGEO_CORE_THREAD_H_
#define _TERGEO_CORE_THREAD_H_
#include <atomic>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <condition_variable>
#include "tergeo/common/macro.h"
#include "tergeo/common/callback/callback_list.h"

namespace tergeo {
namespace common {
class Thread {
public:
    Thread();  
    virtual ~Thread();

    virtual void start();
    virtual void stop();

    bool isRunning() const {return _is_started.load();}
protected:
    virtual void run() = 0;

    mutable std::mutex _mutex;
    std::atomic<bool> _is_started{false};
    std::thread _thread;
private:
    DISALLOW_COPY_AND_ASSIGN(Thread);
};

class ThreadNotify : public Thread, public tergeo::common::CallbackList {
public:
    ThreadNotify();
    ~ThreadNotify() override;
    
    void stop() override;
    void notify();
    
protected:
    void run() override;
protected:
    std::condition_variable _condition_var;
private:
    DISALLOW_COPY_AND_ASSIGN(ThreadNotify);
};

class ThreadTimer : public Thread, public tergeo::common::CallbackList {
public:
    typedef typename std::function<void()> Callback;
    ThreadTimer();
    ~ThreadTimer() override;
    
    void setPeriod(float period_ms);
    float getPeriod() const;
protected:
    void run() override;
protected:
    std::atomic<int64_t> _period_us{100 * 1000};
private:
    DISALLOW_COPY_AND_ASSIGN(ThreadTimer);
};

}
}

#endif