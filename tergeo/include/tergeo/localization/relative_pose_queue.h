#ifndef _TERGEO_LOCALIZATION_RELATIVE_POSE_QUEUE_H
#define _TERGEO_LOCALIZATION_RELATIVE_POSE_QUEUE_H
#include "tergeo/localization/utils.h"
namespace tergeo {
namespace localization {

class RelativePoseQueuePrivate;
class RelativePoseQueue {
public:
    RelativePoseQueue();
    virtual ~RelativePoseQueue();
    
    void resize(int size);

    // from_stamp > to_stamp
    RelativePose getPose(const TimeStamp from_stamp, const TimeStamp to_stamp) const;
    TimeStamp getLatestTimeStamp() const;
    
    void enqueue(const TimeStamp stamp, 
        const common::math::Pose3d& pose);
    
private:
    RelativePoseQueuePrivate* _ptr = nullptr;
};

}
}

#endif