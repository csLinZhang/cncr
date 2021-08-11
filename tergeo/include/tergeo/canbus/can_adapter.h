#ifndef _TERGEO_DRIVERS_CANBUS_CAN_ADAPTER_H_
#define _TERGEO_DRIVERS_CANBUS_CAN_ADAPTER_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/canbus/can_frame.h"
namespace tergeo {
namespace canbus {

class CanAdapter : public tergeo::core::IPlugin {
    DECLARE_FACTORY(CanAdapter)
    DECLARE_DEFAULT_STRUCTOR(CanAdapter)
public:    
    void setCanPort(uint32_t port);
    uint32_t getCanPort() const;
    void addFilterID(uint32_t id);
    void setMaxReceivedFrameNum(uint32_t max_num);
    uint32_t getMaxReceivedFrameNum() const;

    virtual common::Status init() = 0;
    virtual common::Status start() = 0;
    virtual void stop() = 0;

    virtual bool send(const std::vector<CanFrame>& frames) = 0;
    virtual bool receive(std::vector<CanFrame>& frames) = 0;
    
protected:
    uint32_t _max_received_frame_num = 10;
    uint32_t _can_port = 0;
    std::vector<uint32_t> _can_filter_id_vec;
};

#define REGISTER_CAN_ADAPTER_CPP(sub_adapter) REGISTER_CLASS_CPP(tergeo::canbus::CanAdapter, sub_adapter)

}
}

#endif