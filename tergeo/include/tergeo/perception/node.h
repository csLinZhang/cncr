#ifndef _TERGEO_PERCEPTION_NODE_H_
#define _TERGEO_PERCEPTION_NODE_H_
#include <vector>
#include <string>
#include "tergeo/core/factory.h"
#include "tergeo/perception/utils.h"
#include "tergeo/perception/edge.h"

namespace tergeo {
namespace perception {

class Node : public tergeo::core::IPlugin {
    DECLARE_FACTORY(Node)
    DECLARE_DEFAULT_STRUCTOR(Node)
public:    
    void setNodeID(NodeID node_id); 
    NodeID getNodeID() const;

    void setEdges(const std::vector<Edge>& edges);
    const std::vector<Edge>& getEdges() const;

    void setSyncTimeInterval(int64_t sync_time_interval_ms);
    
    void transmit();
    void addChild(Node* child);

    virtual common::Status init() = 0;
    virtual common::Status start() = 0;
    
    virtual bool process() = 0;
    virtual void registerSharedData() const = 0;

protected:
    double _sync_time_interval_s = -1;
    NodeID _node_id = -1;
    std::vector<Edge> _edges;
private:
    std::vector<Node*> _children;
    DISALLOW_COPY_AND_ASSIGN(Node);
};
#define REGISTER_NODE_CLASS_CPP(sub_node) REGISTER_CLASS_CPP(tergeo::perception::Node, sub_node)

}
}
#endif