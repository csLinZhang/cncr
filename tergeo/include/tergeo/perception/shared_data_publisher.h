#ifndef _TERGEO_PERCEPTION_SHARED_DATA_PUBLISHER_H
#define _TERGEO_PERCEPTION_SHARED_DATA_PUBLISHER_H
#include "tergeo/perception/utils.h"
#include "tergeo/perception/global_data.h"

namespace tergeo {
namespace perception {

template <typename T> 
class SharedDataPublisher {
    DECLARE_DEFAULT_STRUCTOR(SharedDataPublisher)
protected:
    void publishSharedData(const std::shared_ptr<T>& data_ptr) {
        _shared_data_list_publisher->push(data_ptr);
    }
    void initPublisherSharedData(const NodeID& node_id) {
        _shared_data_list_publisher = GlobalData::Instance()->getSharedData(node_id)->cast<SharedDataList<T> >();
        CHECK(_shared_data_list_publisher) << "NULL shared data out, NodeID: " << node_id;
    }
    void registerNodeSharedData(const NodeID& node_id) const {
        GlobalData::Instance()->registerSharedData<T>(node_id);
    }
protected:
    SharedDataList<T>* _shared_data_list_publisher = nullptr;
};


}
}

#endif