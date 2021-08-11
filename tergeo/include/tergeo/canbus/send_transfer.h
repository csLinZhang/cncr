#ifndef _TERGEO_CANBUS_SEND_TRANSFER_H
#define _TERGEO_CANBUS_SEND_TRANSFER_H
#include "tergeo/common/thread/thread.h"
#include "tergeo/canbus/can_adapter.h"
#include "tergeo/canbus/can_data_sender.h"
namespace tergeo {
namespace canbus {
class SendTransfer {
    DECLARE_DEFAULT_STRUCTOR(SendTransfer)
public:    
    void start();
    void stop();

    void setAdapter(CanAdapter* adapter);
        
    void addSender(uint32_t id, BaseCanDataSender* sender);
    
    void process();
private:
    CanAdapter* _can_adapter = nullptr;
    std::unordered_map<uint32_t, BaseCanDataSender*> _sender_map;
    std::unordered_set<BaseCanDataSender*> _sender_set;
    tergeo::common::ThreadTimer _thread;
    std::vector<CanFrame> _can_frames;
};
}
}
#endif