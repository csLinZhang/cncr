#ifndef _TERGEO_LOCALIZATION_BASE_RELATIVE_LOCALIZER_H_
#define _TERGEO_LOCALIZATION_BASE_RELATIVE_LOCALIZER_H_
#include "tergeo/localization/utils.h"
#include "tergeo/core/factory.h"
#include "tergeo/localization/relative_pose_queue.h"

namespace tergeo {
namespace localization {

class BaseRelativeLocalizer : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseRelativeLocalizer)
    DECLARE_DEFAULT_STRUCTOR(BaseRelativeLocalizer)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}

    RelativePose getPose(const TimeStamp from_stamp, const TimeStamp to_time) const;
    TimeStamp getLatestTimeStamp() const;
protected:
    void resizeQueue(int size);
protected:
    std::shared_ptr<RelativePoseQueue> _rel_pose_queue;    
};
#define REGISTER_RELATIVE_LOCALIZER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::localization::BaseRelativeLocalizer, sub_class)
}
} // tergeo 
#endif