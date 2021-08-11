#ifndef _TERGEO_CANBUS_CAN_DATA_RECEIVER_H
#define _TERGEO_CANBUS_CAN_DATA_RECEIVER_H
#include "tergeo/common/thread/thread.h"
#include "tergeo/canbus/can_recv_data.h"
namespace tergeo {
namespace canbus {

class BaseCanDataReceiver {
    DECLARE_DEFAULT_STRUCTOR(BaseCanDataReceiver)
public:
    
    void start();
    void stop();

    void notify();

    bool updateCanFrame(const CanFrame& frame);
    
    virtual std::vector<uint32_t> getCanFrameIDVec() const = 0;
    virtual void parseOnce() = 0;
    
    tergeo::common::ThreadNotify* getThread();
protected:
    mutable std::mutex _mutex;
    std::unordered_map<uint32_t, CanFrame> _cam_frame_map;
    std::atomic<bool> _need_update{false};
    tergeo::common::ThreadNotify _thread;
};

template <class T>
class CanDataReceiver : public BaseCanDataReceiver {
    DECLARE_DEFAULT_STRUCTOR(CanDataReceiver)
public:
    typedef T DataType;
    typedef CanRecvData<DataType> CanRecvDataT;
    
    void getRecvData(DataType& data) {
        std::lock_guard<std::mutex> lock(_mutex);
        data = _receiver_data;
    }

    template <class RecvDataType> 
    void addCanRecvData() {
        std::shared_ptr<CanRecvDataT> can_recv_data(new RecvDataType());
        if (_recv_can_data_map.find(can_recv_data->ID()) != _recv_can_data_map.end()) {
            return;
        }
        _recv_can_data_vec.emplace_back(can_recv_data);
        _recv_can_data_map[can_recv_data->ID()] = can_recv_data.get();
        _cam_frame_map[can_recv_data->ID()].id = can_recv_data->ID();
        _cam_frame_map[can_recv_data->ID()].length = CANBUS_MESSAGE_LENGTH;
    }
    
    std::vector<uint32_t> getCanFrameIDVec() const override;
    void parseOnce() override;
protected:
    DataType _receiver_data;
    std::vector<std::shared_ptr<CanRecvDataT> > _recv_can_data_vec;
    std::unordered_map<uint32_t, CanRecvDataT* > _recv_can_data_map;
    DISALLOW_COPY_AND_ASSIGN(CanDataReceiver);
};

template <class T>
std::vector<uint32_t> CanDataReceiver<T>::getCanFrameIDVec() const {
    std::vector<uint32_t> id_vec;
    for (int i = 0; i < _recv_can_data_vec.size(); ++i) {
        id_vec.push_back(_recv_can_data_vec[i]->ID());
    }
    return std::move(id_vec);
}
template <class T>
void CanDataReceiver<T>::parseOnce() {
    std::lock_guard<std::mutex> lock(_mutex);
    for (const auto& iter : _cam_frame_map) {
        if (_recv_can_data_map.find(iter.first) == _recv_can_data_map.end()) {
            continue;
        }
        _recv_can_data_map[iter.first]->parse(iter.second.data, iter.second.length, _receiver_data);
    }
}

}
}
#endif