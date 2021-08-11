#ifndef _TERGEO_CANBUS_CAN_DATA_SENDER_H
#define _TERGEO_CANBUS_CAN_DATA_SENDER_H
#include "tergeo/canbus/can_send_data.h"
namespace tergeo {
namespace canbus {

class BaseCanDataSender {
    DECLARE_DEFAULT_STRUCTOR(BaseCanDataSender)
public:
    bool updateCanFrame(const uint32_t id, CanFrame& frame);
    
    virtual std::vector<uint32_t> getCanFrameIDVec() const = 0;
    virtual void unparseOnce() = 0;
protected:
    mutable std::mutex _mutex;
    std::unordered_map<uint32_t, CanFrame> _cam_frame_map;
};

class CanDataSender : public BaseCanDataSender {
    DECLARE_DEFAULT_STRUCTOR(CanDataSender)
public:
    template <class SendDataType>
    SendDataType* addCanSendData() {
        std::shared_ptr<CanSendData> can_send_data(new SendDataType());
        if (_send_can_data_map.find(can_send_data->ID()) != _send_can_data_map.end()) {
            return _send_can_data_map[can_send_data->ID()]->cast<SendDataType>();
        }
        _send_can_data_vec.emplace_back(can_send_data);
        _send_can_data_map[can_send_data->ID()] = can_send_data.get();
        _cam_frame_map[can_send_data->ID()].id = can_send_data->ID();
        _cam_frame_map[can_send_data->ID()].length = 0;//CANBUS_MESSAGE_LENGTH;
        return can_send_data.get()->cast<SendDataType>();
    }
    CanSendData* getCanSendData(const uint32_t message_id) {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_send_can_data_map.find(message_id) == _send_can_data_map.end()) {
            return nullptr;
        }
        return _send_can_data_map[message_id];
    }
    std::vector<uint32_t> getCanFrameIDVec() const override;
    void unparseOnce() override;
private:
    std::vector<std::shared_ptr<CanSendData> > _send_can_data_vec;
    std::unordered_map<uint32_t, CanSendData* > _send_can_data_map;
    DISALLOW_COPY_AND_ASSIGN(CanDataSender);
};

}
}

#endif