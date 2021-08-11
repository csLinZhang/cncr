#ifndef _TERGEO_CANBUS_TEST_FAKE_CAN_ADAPTER_
#define _TERGEO_CANBUS_TEST_FAKE_CAN_ADAPTER_

#include "tergeo/canbus/can_adapter.h"

namespace tergeo {
namespace canbus {
class FakeCanAdapter : public tergeo::canbus::CanAdapter {
public:
    FakeCanAdapter() : tergeo::canbus::CanAdapter() {}

    ~FakeCanAdapter() {}

    virtual common::Status init() {
        std::cout << "init fake can adapter!" << std::endl;
        return common::StatusOK();
    }
    virtual common::Status start() {
        std::cout << "start fake can adapter!" << std::endl;
        return common::StatusOK();
    }
    virtual void stop() {
        std::cout << "stop fake can adapter!" << std::endl;
    }

    virtual bool send(const std::vector<CanFrame>& frames)  {
        if (frames.size() > 0) {
            std::cout << "send data: " << frames[0].id << " " << int(frames[0].data[0]) << std::endl;
        }
        return true;
    }

    virtual bool receive(std::vector<CanFrame>& frames);
private:

};

}
}

#endif