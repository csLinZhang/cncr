#ifndef _TERGEO_PERCEPTION_TOPIC_IN_NODE_H
#define _TERGEO_PERCEPTION_TOPIC_IN_NODE_H
#include "tergeo/perception/node.h"
#include "tergeo/perception/topic_receiver.h"
#include "tergeo/perception/shared_data_publisher.h"

namespace tergeo {
namespace perception {
template<typename Mout, typename M1>
class TopicInNode : public Node, public TopicReceiver<M1>, public SharedDataPublisher<Mout> {
    DECLARE_DEFAULT_STRUCTOR(TopicInNode)
public:
    common::Status start() override {
        TopicReceiver<M1>::initReceiverAdapter();
        SharedDataPublisher<Mout>::initPublisherSharedData(_node_id);
        return common::StatusOK();
    }
    void registerSharedData() const override {
        SharedDataPublisher<Mout>::registerNodeSharedData(_node_id);
    }
    void publishAndTransmit(const std::shared_ptr<Mout>& data_ptr) {
        SharedDataPublisher<Mout>::publishSharedData(data_ptr);
        Node::transmit();
    }
    bool process() override {
        // do nothing
        return true;
    }
};
}
}

#endif