#ifndef _TERGEO_PERCEPTION_TOPIC_IN_OUT_NODE_H
#define _TERGEO_PERCEPTION_TOPIC_IN_OUT_NODE_H
#include "tergeo/perception/node.h"
#include "tergeo/perception/topic_receiver.h"
#include "tergeo/perception/topic_publisher.h"

namespace tergeo {
namespace perception {
template<typename Mout, typename M1>
class TopicInOutNode : public Node, public TopicReceiver<M1>, public TopicPublisher<Mout> {
    DECLARE_DEFAULT_STRUCTOR(TopicInOutNode)
public:
    common::Status start() override {
        TopicReceiver<M1>::initReceiverAdapter();
        TopicPublisher<Mout>::initPublisherAdapter();
        return common::StatusOK();
    }
    void registerSharedData() const override {}
    
    bool process() override {return true;}
};

}
}

#endif