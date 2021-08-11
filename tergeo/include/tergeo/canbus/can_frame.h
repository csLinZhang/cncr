#ifndef _TERGEO_CANBUS_CAN_FRAME_H_
#define _TERGEO_CANBUS_CAN_FRAME_H_
#include "tergeo/common/common.hpp"
namespace tergeo {
namespace canbus {
const int32_t CAN_FRAME_SIZE = 8;
//const int32_t MAX_CAN_SEND_FRAME_LEN = 1;
//const int32_t MAX_CAN_RECV_FRAME_LEN = 10;

const int32_t CANBUS_MESSAGE_LENGTH = 8;  // according to ISO-11891-1
const int32_t MAX_CAN_PORT = 3;


struct CanFrame {
    CanFrame() : id(0), length(0) {
        std::memset(data, 0, sizeof(data));
    }
    uint32_t id;
    /// Message length
    uint8_t length; // usually 8
    /// Message content
    uint8_t data[8];    
    
    void copyTo(CanFrame& other) const {
        other.id = id;
        other.length = length;
        std::copy(data, data + 8, other.data);
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "id: 0x" << tergeo::common::byte::ByteToHex(id)
            << ",length :" << static_cast<int>(length) << ",data: ";
        for (uint8_t i = 0; i < length; ++i) {
            ss << tergeo::common::byte::ByteToHex(data[i]) << " ";
        }
        return ss.str();
    }
};

}
}

#endif