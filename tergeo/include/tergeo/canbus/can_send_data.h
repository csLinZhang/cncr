#ifndef _TERGEO_CANBUS_CAN_SEND_DATA_H
#define _TERGEO_CANBUS_CAN_SEND_DATA_H
#include "tergeo/canbus/can_frame.h"

namespace tergeo {
namespace canbus {

class CanSendData {
    DECLARE_DEFAULT_STRUCTOR(CanSendData)
public:    
    virtual uint32_t ID() const = 0; // {return 0x00;}

    virtual bool update(uint8_t* data) = 0;

    virtual void reset() {}

    virtual uint32_t getPeriod() const {
        const uint32_t CONST_PERIOD = 100 * 1000; // 100 ms
        return CONST_PERIOD;
    }
    virtual uint32_t getLength() const {return CANBUS_MESSAGE_LENGTH;}

    template <typename T> 
    T* cast() {return dynamic_cast<T*>(this);}
};
    
}
}
#endif