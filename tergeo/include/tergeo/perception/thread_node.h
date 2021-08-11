#ifndef _TERGEO_PERCEPTION_THREAD_NODE_H
#define _TERGEO_PERCEPTION_THREAD_NODE_H
#include "tergeo/perception/node.h"
#include "tergeo/common/thread/thread.h"

namespace tergeo {
namespace perception {

class ThreadNode : public tergeo::perception::Node {
public:
    ThreadNode() = default;
    virtual ~ThreadNode();
    
    common::Status start() override;

    bool process() override;

    void registerSharedData() const override {}
    
    virtual void proc() = 0;
protected:
    tergeo::common::ThreadNotify _notify_thread;
};

}
}

#endif