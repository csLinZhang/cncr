#ifndef _TERGEO_CANBUS_RECV_TRANSFER_H
#define _TERGEO_CANBUS_RECV_TRANSFER_H
#include "tergeo/common/thread/thread.h"
#include "tergeo/canbus/can_adapter.h"
#include "tergeo/canbus/can_data_receiver.h"
namespace tergeo {
namespace canbus {
class RecvTransfer : public tergeo::common::Thread {
    DECLARE_DEFAULT_STRUCTOR(RecvTransfer)
public:    
    void setAdapter(CanAdapter* adapter);

    void addReceiver(uint32_t id, BaseCanDataReceiver* receiver);

protected:
    void run() override;
private:
    CanAdapter* _can_adapter = nullptr;
    std::unordered_map<uint32_t, BaseCanDataReceiver*> _receiver_map;
};
}
}

#endif