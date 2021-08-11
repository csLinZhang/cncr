#ifndef TERGEO_PERCEPTION_GLOBAL_DATA_H_
#define TERGEO_PERCEPTION_GLOBAL_DATA_H_
#include "tergeo/perception/utils.h"
#include "tergeo/perception/edge.h"
#include "tergeo/perception/shared_data.h"

namespace tergeo {
namespace perception {
class GlobalData {
public:
    ~GlobalData() {}
    bool hasSharedData(const NodeID& node_id);
    SharedData* getSharedData(const NodeID& node_id) const;
    
    template <typename T>
    SharedDataList<T>* getSharedDataList(const Edge& edge) const {
        SharedDataList<T>* shared_data = getSharedData(edge.from_node_id)->cast<SharedDataList<T> >();
        CHECK(shared_data) << "Empty data, NodeID: " << edge.from_node_id;
        return shared_data; 
    }

    template <typename T>
    void registerSharedData(const NodeID& node_id) {
        std::lock_guard<std::mutex> lock(_mutex);
        CHECK(_shared_data_map.find(node_id) == _shared_data_map.end()) 
            << "Confilct shard_data, node id: " << node_id;
        _shared_data_map[node_id].reset(new SharedDataList<T>());
    }
private:
    mutable std::mutex _mutex;
    std::unordered_map<NodeID, SharedData::Ptr> _shared_data_map;
    DECLARE_SINGLETON(GlobalData);
};
}
}
#endif