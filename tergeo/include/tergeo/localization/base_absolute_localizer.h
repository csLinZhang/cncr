#ifndef _TERGEO_LOCALIZATION_BASE_ABSOLUTE_LOCALIZER_H_
#define _TERGEO_LOCALIZATION_BASE_ABSOLUTE_LOCALIZER_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "tergeo/localization/absolute_pose_queue.h"

namespace tergeo {
namespace localization {

class BaseAbsoluteLocalizer : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseAbsoluteLocalizer)
    DECLARE_DEFAULT_STRUCTOR(BaseAbsoluteLocalizer)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}

    virtual AbsolutePose getNearestPose(const TimeStamp stamp) const;
    virtual AbsolutePose getLatestPose() const;
    TimeStamp getLatestTimeStamp() const;
protected:
    void resizeQueue(int size);
protected:
    std::shared_ptr<AbsolutePoseQueue> _abs_pose_queue;  
};
#define REGISTER_ABSOLUTE_LOCALIZER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::localization::BaseAbsoluteLocalizer, sub_class)
}
} // tergeo 
#endif