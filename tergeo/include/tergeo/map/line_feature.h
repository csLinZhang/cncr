#ifndef _TERGEO_MAP_LINE_FEATURE_H
#define _TERGEO_MAP_LINE_FEATURE_H

#include "tergeo/common/math/point.h"
#include "tergeo/map/proto/line_feature.pb.h"

namespace tergeo {
namespace map {

class LineFeature {
public:
    LineFeature() = default;
    virtual ~LineFeature() = default;
    
    const common::math::Point2d& getStartPoint() const;
    const common::math::Point2d& getEndPoint() const;

    common::math::Polyline2d getSamplingPoints(double step = 1) const;
protected:
    common::math::Point2d _start_point;
    common::math::Point2d _end_point; 
};

class StopSign final : public LineFeature {
public:
    StopSign() = default;
    ~StopSign() = default;

    StopSign(const proto::StopSign& proto_stop_sign);

    std::string id() const;

    void setProtoStopSign(const proto::StopSign& proto_stop_sign);
    const proto::StopSign& getProtoStopSign() const;
private:
    proto::StopSign _proto_stop_sign;
};

class SpeedBump final : public LineFeature {
public:
    SpeedBump() = default;
    ~SpeedBump() = default;

    SpeedBump(const proto::SpeedBump& proto_speed_bump);

    std::string id() const;

    void setProtoSpeedBump(const proto::SpeedBump& proto_speed_bump);
    const proto::SpeedBump& getProtoSpeedBump() const;
private:
    proto::SpeedBump _proto_speed_bump;
};
}
}
#endif