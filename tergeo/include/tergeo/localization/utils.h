#ifndef _TERGEO_LOCALIZATION_UTILS_H_
#define _TERGEO_LOCALIZATION_UTILS_H_
#include "tergeo/common/common.hpp"

namespace tergeo {
namespace localization {

using TimeStamp = int64_t;
inline
TimeStamp Now() {
    return tergeo::common::time::Clock::NowInMilliSeconds();
}
inline
TimeStamp FromRosTime(const ros::Time& ros_time) {
    return ros_time.toNSec() * 1e-6;
}

struct RelativePose {
    RelativePose() : valid(false), from_stamp(0), to_stamp(0) {}
    RelativePose(const TimeStamp from_stamp_, TimeStamp to_stamp_) 
        : valid(true), from_stamp(from_stamp_), to_stamp(to_stamp_) {}
    TimeStamp from_stamp;
    TimeStamp to_stamp;
    common::math::Pose3d pose;
    //double covariance[36];
    bool valid;
};

struct AbsolutePose {
    AbsolutePose() : valid(false) {}
    AbsolutePose(const TimeStamp stamp_) : valid(true), stamp(stamp_) {}
    TimeStamp stamp;
    common::math::Pose3d pose;
    //double covariance[36];
    bool valid;
};
}
}

#endif