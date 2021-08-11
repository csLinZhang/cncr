#ifndef _TERGEO_CANBUS_CAN_RECV_DATA_H
#define _TERGEO_CANBUS_CAN_RECV_DATA_H
#include "tergeo/canbus/can_frame.h"

namespace tergeo {
namespace canbus {

template <typename T>
class CanRecvData {
    DECLARE_DEFAULT_STRUCTOR(CanRecvData)
public:
    typedef T DataType;

    virtual uint32_t ID() const = 0; // {return 0x00;}
    // parse data
    virtual void parse(const uint8_t* data, const uint8_t length, DataType& recv_data) const = 0;
   
    virtual uint32_t getLength() const {return CANBUS_MESSAGE_LENGTH;}

};
    
}
}
#endif