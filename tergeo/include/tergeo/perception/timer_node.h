#ifndef _TERGEO_PERCEPTION_TIMER_NODE_H
#define _TERGEO_PERCEPTION_TIMER_NODE_H
#include "tergeo/perception/node.h"
#include "tergeo/common/thread/thread.h"

namespace tergeo {
namespace perception {

class TimerNode : public tergeo::perception::Node {
public:
    TimerNode() = default;
    virtual ~TimerNode();
    
    common::Status start() override;
    bool process() override;

    void registerSharedData() const override {}
    void setTimerPeriod(float period_ms);

    virtual void proc() = 0;
    
protected:
    tergeo::common::ThreadTimer _timer_thread;
};

}
}

#endif