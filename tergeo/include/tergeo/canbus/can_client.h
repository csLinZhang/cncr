#ifndef _TERGEO_CNABUS_CANCLIENT_H_
#define _TERGEO_CNABUS_CANCLIENT_H_

#include "tergeo/canbus/can_adapter.h"
namespace tergeo {
namespace canbus {
class BaseCanDataReceiver;
class BaseCanDataSender;
class CanClientPrivate;
class CanClient final {
public:
    CanClient();
    virtual ~CanClient();
    
    common::Status init(const std::string& cfg_filename);

    common::Status start();

    void stop();
    
    CanAdapter* getCanAdapter(uint32_t port);

    void addCanDataReceiver(uint32_t port, BaseCanDataReceiver* receiver);
    void addCanDataSender(uint32_t port, BaseCanDataSender* sender);

private:
    CanClientPrivate* _ptr;
};

}
}

#endif