#ifndef _TERGEO_COMMON_THREAD_THREAD_POOL_H_
#define _TERGEO_COMMON_THREAD_THREAD_POOL_H_
#include <tergeo/common/macro.h>
#include <tergeo/common/log.h>
#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>
#include <functional>

namespace tergeo {
namespace common {

class ThreadPool final {
public:
    using Task = std::function<void()>;
    ~ThreadPool();
    bool start(int thread_num = 8);
    void stop();
    void setMaxTaskLimitNum(int max_task_limit_num);
    template<class F, class... Args>
    auto schedule(F&& f, Args&&... args) 
            ->std::future<decltype(f(args...))> {
        CHECK(_is_started.load()) << "ThreadPoll is Stopped";
        using RetType = decltype(f(args...)); 
        auto task = std::make_shared<std::packaged_task<RetType()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<RetType> future = task->get_future();
        {
            std::lock_guard<std::mutex> lock(_mutex);
            while (_tasks.size() > _max_task_limit_num) {
                AWARN << "ThreadPool is FULL, size: " << _tasks.size();
                _tasks.pop();
            }
            _tasks.emplace([task](){(*task)();});
        }
        _condition_var.notify_one();
        return future;
    }

private:
    std::mutex _mutex;
    std::atomic<bool> _is_started{false};
    std::queue<Task> _tasks;
    std::atomic<int> _max_task_limit_num{1000};
    std::vector<std::thread> _thread_pool;
    std::condition_variable _condition_var;
    DECLARE_SINGLETON(ThreadPool);
};
}
}

#endif