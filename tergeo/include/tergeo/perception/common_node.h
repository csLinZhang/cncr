#ifndef _TERGEO_PERCEPTION_COMMON_NODE_H_
#define _TERGEO_PERCEPTION_COMMON_NODE_H_
#include "tergeo/perception/node.h"
#include "tergeo/perception/shared_data_fusion.h"
#include "tergeo/perception/shared_data_publisher.h"

namespace tergeo {
namespace perception {

template<typename Mout = NullType, typename M1 = NullType, typename M2 = NullType, 
    typename M3 = NullType, typename M4 = NullType>
class CommonNode : public Node, public SharedDataFusion<M1, M2, M3, M4>, public SharedDataPublisher<Mout> {
public:
    CommonNode() : Node(), SharedDataFusion<M1, M2, M3, M4>(), SharedDataPublisher<Mout>() {}
    virtual ~CommonNode() {}

    virtual common::Status start() final {
        SharedDataFusion<M1, M2, M3, M4>::initFusionSharedData(_edges);
        SharedDataPublisher<Mout>::initPublisherSharedData(_node_id);
        return common::StatusOK();
    }

    void registerSharedData() const override {
        SharedDataPublisher<Mout>::registerNodeSharedData(_node_id);
    }

    bool process() override {
        return SharedDataFusion<M1, M2, M3, M4>::fusion(_sync_time_interval_s);
    }
    void publishAndTransmit(const std::shared_ptr<Mout>& data_ptr) {
        SharedDataPublisher<Mout>::publishSharedData(data_ptr);
        Node::transmit();
    }
};

template<typename Mout, typename M1>
class CommonNode<Mout, M1, NullType, NullType, NullType> : 
    public Node, public SharedDataFusion<M1>, public SharedDataPublisher<Mout> {
public:
    CommonNode() : Node(), SharedDataFusion<M1>(), SharedDataPublisher<Mout>() {}
    virtual ~CommonNode() {}

    virtual common::Status start() final {
        SharedDataFusion<M1>::initFusionSharedData(_edges);
        SharedDataPublisher<Mout>::initPublisherSharedData(_node_id);
        return common::StatusOK();
    }
    void registerSharedData() const override {
        SharedDataPublisher<Mout>::registerNodeSharedData(_node_id);
    }
    bool process() override {
        return SharedDataFusion<M1>::fusion(_sync_time_interval_s);
    }
    void publishAndTransmit(const std::shared_ptr<Mout>& data_ptr) {
        SharedDataPublisher<Mout>::publishSharedData(data_ptr);
        Node::transmit();
    }
};

template<typename Mout, typename M1, typename M2>
class CommonNode<Mout, M1, M2, NullType, NullType> : 
    public Node, public SharedDataFusion<M1, M2>, public SharedDataPublisher<Mout> {
public:
    CommonNode() : Node(), SharedDataFusion<M1, M2>(), SharedDataPublisher<Mout>() {}
    virtual ~CommonNode() {}
   
    virtual common::Status start() final {
        SharedDataFusion<M1, M2>::initFusionSharedData(_edges);
        SharedDataPublisher<Mout>::initPublisherSharedData(_node_id);
        return common::StatusOK();
    }

    void registerSharedData() const override {
        SharedDataPublisher<Mout>::registerNodeSharedData(_node_id);
    }
    bool process() override {
        return SharedDataFusion<M1, M2>::fusion(_sync_time_interval_s);
    }
    void publishAndTransmit(const std::shared_ptr<Mout>& data_ptr) {
        SharedDataPublisher<Mout>::publishSharedData(data_ptr);
        Node::transmit();
    }
};

template<typename Mout, typename M1, typename M2, typename M3>
class CommonNode<Mout, M1, M2, M3, NullType> : 
    public Node, public SharedDataFusion<M1, M2, M3>, public SharedDataPublisher<Mout> {
public:
    CommonNode() : Node(), SharedDataFusion<M1, M2, M3>(), SharedDataPublisher<Mout>() {}
    virtual ~CommonNode() {}
    
    virtual common::Status start() final {
         SharedDataFusion<M1, M2, M3>::initFusionSharedData(_edges);
        SharedDataPublisher<Mout>::initPublisherSharedData(_node_id);
        return common::StatusOK();
    }
    void registerSharedData() const override {
        SharedDataPublisher<Mout>::registerNodeSharedData(_node_id);
    }
    bool process() override {
        return SharedDataFusion<M1, M2, M3>::fusion(_sync_time_interval_s);
    }
    void publishAndTransmit(const std::shared_ptr<Mout>& data_ptr) {
        SharedDataPublisher<Mout>::publishSharedData(data_ptr);
        Node::transmit();
    }
};

}
}
#endif