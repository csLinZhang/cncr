#ifndef _TERGEO_LOCALIZATION_ABSOLUTE_POSE_QUEUE_H
#define _TERGEO_LOCALIZATION_ABSOLUTE_POSE_QUEUE_H
#include "tergeo/localization/utils.h"
namespace tergeo {
namespace localization {

class AbsolutePoseQueuePrivate;
class AbsolutePoseQueue {
public:
    AbsolutePoseQueue();
    virtual ~AbsolutePoseQueue();
    
    void resize(int size);
    // from_stamp > to_stamp
    AbsolutePose getNearestPose(const TimeStamp stamp) const;
    AbsolutePose getLatestPose() const;
    TimeStamp getLatestTimeStamp() const;
    
    void enqueue(const TimeStamp stamp, const common::math::Pose3d& pose);
private:
    AbsolutePoseQueuePrivate* _ptr = nullptr;
};

}
}

#endif