#ifndef _TERGEO_PREDICTION_POSE_QUEUE_H
#define _TERGEO_PREDICTION_POSE_QUEUE_H
#include "tergeo/framework/topic_holder.h"
#include "tergeo/common/common.hpp"

namespace tergeo {
namespace prediction {

class PoseQueuePrivate;
class PoseQueue {
public:
    PoseQueue();
    virtual ~PoseQueue();
    
    void resize(int size);
    common::math::Pose3d getNearestPose(const double stamp) const;

    void enqueue(const double stamp, const common::math::Pose3d& pose);
private:
    PoseQueuePrivate* _ptr = nullptr;
    
};

}
}

#endif