#ifndef _TERGEO_PERCEPTION_SHARED_DATA_H
#define _TERGEO_PERCEPTION_SHARED_DATA_H
#include "tergeo/common/macro.h"

namespace tergeo {
namespace perception {
class SharedData {
    DECLARE_DEFAULT_STRUCTOR(SharedData)
    DECLARE_SHARED_PTR(SharedData);
public:
    enum AttachDataType {
        DEVICE_ID = 0,
        USER_DEFINE = 100
    };

    void setAttachData(int id, const std::string& attach_data) {
        _attach_data_map[id] = attach_data;
    }
    bool hasAttachData(int id) const {
        return _attach_data_map.find(id) != _attach_data_map.end();
    }
    
    template <typename T> 
    T* cast() {
        return dynamic_cast<T*>(this);
    }
private:
    std::unordered_map<int, std::string> _attach_data_map;
};

template <typename T>
class SharedDataList : public SharedData {
    DECLARE_DEFAULT_STRUCTOR(SharedDataList)
public:
    typedef T DataType;
    typedef std::shared_ptr<T> DataPtr;
    typedef std::pair<double, DataPtr> StampData;
    
    void setDataHistoryLimitNum(int history_limit_num) {
        std::lock_guard<std::mutex> lock(_mutex);
        _max_limit_num = history_limit_num;
    }

    void push(const DataPtr& data_ptr) {
        double now_time_s = tergeo::common::time::Clock::NowInSeconds();
        std::lock_guard<std::mutex> lock(_mutex);
        _data_queue.emplace(std::make_pair(std::move(now_time_s), data_ptr));
        while (_data_queue.size() > _max_limit_num) {
            _data_queue.pop();
        }
    }
    bool getLatestData(StampData& lastest_data) const {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_data_queue.empty()) {
            return false;
        } 
        lastest_data = _data_queue.back();
        return true;
    }
private:
    mutable std::mutex _mutex;
    int _max_limit_num = 5;
    std::queue<StampData> _data_queue;
};
}    
}
#endif
