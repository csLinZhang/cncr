#ifndef _TERGEO_MAP_POLYLINE_FEATURE_H
#define _TERGEO_MAP_POLYLINE_FEATURE_H

#include "tergeo/common/math/point.h"
#include "tergeo/map/proto/polyline_feature.pb.h"

namespace tergeo {
namespace map {

class PolylineFeature {
public:
    PolylineFeature() = default;
    virtual ~PolylineFeature() = default;
    
    const common::math::Polyline2d& getPolyline() const;
    common::math::Polyline2d getSamplingPoints(double step = 1) const;
protected:
    void convertToPolyline(const proto::Polyline& proto_polyline);
protected:
    common::math::Polyline2d _polyline; 
};

class RoadEdge final : public PolylineFeature {
public:
    RoadEdge() = default;
    ~RoadEdge() = default;
    
    RoadEdge(const proto::RoadEdge& proto_road_edge);
    
    std::string id() const;
    void setProtoRoadEdge(const proto::RoadEdge& proto_road_edge);
    const proto::RoadEdge& getProtoRoadEdge() const;
private:
    proto::RoadEdge _proto_road_edge;
};

class LaneLine final : public PolylineFeature {
public:
    LaneLine() = default;
    ~LaneLine() = default;
    
    LaneLine(const proto::LaneLine& proto_lane_line);
    
    std::string id() const;
    void setProtoLaneLine(const proto::LaneLine& proto_lane_line);
    const proto::LaneLine& getProtoLaneLine() const;
private:
    proto::LaneLine _proto_lane_line;
};
}
}
#endif