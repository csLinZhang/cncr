#ifndef _TERGEO_PERCEPTION_COMMON_END_NODE_H_
#define _TERGEO_PERCEPTION_COMMON_END_NODE_H_
#include "tergeo/perception/node.h"
#include "tergeo/perception/shared_data_fusion.h"
#include "tergeo/perception/topic_publisher.h"

namespace tergeo {
namespace perception {
template<typename Mout = NullType, typename M1 = NullType, typename M2 = NullType, 
    typename M3 = NullType, typename M4 = NullType>
class CommonEndNode : public Node, public SharedDataFusion<M1, M2, M3, M4>, public TopicPublisher<Mout> {
public:
    CommonEndNode() : Node(), SharedDataFusion<M1, M2, M3, M4>(), TopicPublisher<Mout>() {}
    virtual ~CommonEndNode() {}
    
    virtual common::Status start() final {
        SharedDataFusion<M1, M2, M3, M4>::initFusionSharedData(_edges);
        TopicPublisher<Mout>::initPublisherAdapter();
        return common::StatusOK();
    }
    void registerSharedData() const override {}

    bool process() override {
        return SharedDataFusion<M1, M2, M3, M4>::fusion(_sync_time_interval_s);
    }
    
};
template<typename Mout, typename M1>
class CommonEndNode<Mout, M1, NullType, NullType, NullType> : 
    public Node, public SharedDataFusion<M1>, public TopicPublisher<Mout> {
public:
    CommonEndNode() : Node(), SharedDataFusion<M1>(), TopicPublisher<Mout>() {}
    virtual ~CommonEndNode() {}
    
    virtual common::Status start() final {
        SharedDataFusion<M1>::initFusionSharedData(_edges);
        TopicPublisher<Mout>::initPublisherAdapter();
        return common::StatusOK();
    }
    void registerSharedData() const override {}
    
    bool process() override {
        return SharedDataFusion<M1>::fusion(_sync_time_interval_s);
    }
};
template<typename Mout, typename M1, typename M2>
class CommonEndNode<Mout, M1, M2, NullType, NullType> : 
    public Node, public SharedDataFusion<M1, M2>, public TopicPublisher<Mout> {
public:
    CommonEndNode() : Node(), SharedDataFusion<M1, M2>(), TopicPublisher<Mout>() {}
    virtual ~CommonEndNode() {}
    
    virtual common::Status start() final {
        SharedDataFusion<M1, M2>::initFusionSharedData(_edges);
        TopicPublisher<Mout>::initPublisherAdapter();
        return common::StatusOK();
    }
    void registerSharedData() const override {
        // do nothing
    }
    bool process() override {
        return SharedDataFusion<M1, M2>::fusion(_sync_time_interval_s);
    }
};

template<typename Mout, typename M1, typename M2, typename M3>
class CommonEndNode<Mout, M1, M2, M3, NullType> : public Node, 
    public SharedDataFusion<M1, M2, M3>, public TopicPublisher<Mout> {
public:
    CommonEndNode() : Node(), SharedDataFusion<M1, M2, M3>(), TopicPublisher<Mout>() {}
    virtual ~CommonEndNode() {}

    virtual common::Status start() final {
        SharedDataFusion<M1, M2, M3>::initFusionSharedData(_edges);
        TopicPublisher<Mout>::initPublisherAdapter();
        return common::StatusOK();
    }
    void registerSharedData() const override {}

    bool process() override {
        return SharedDataFusion<M1, M2, M3>::fusion(_sync_time_interval_s);
    }
};
}
}
#endif