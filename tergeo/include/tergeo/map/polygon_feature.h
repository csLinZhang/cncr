#ifndef _TERGEO_HD_MAP_POLYGON_FEATURE_H
#define _TERGEO_HD_MAP_POLYGON_FEATURE_H

#include "tergeo/common/math/point.h"
#include "tergeo/common/math/rect.h"
#include "tergeo/map/proto/polygon_feature.pb.h"

namespace tergeo {
namespace map {

class PolygonFeature {
public:
    PolygonFeature() = default;
    virtual ~PolygonFeature() = default;
    
    const std::vector<common::math::Polyline2d>& getIncludePolygons() const;
    const std::vector<common::math::Polyline2d>& getExcludePolygons() const;

    common::math::Polyline2d getSamplingPoints(double step = 1) const;

    bool isPointIn(const double X, const double Y) const;
    const common::math::Rect2d& getBoundingRect() const;
protected:
    void convertToPolygon(const proto::Polygon& proto_polygon);
    void computeBoundingRect();
protected:
    common::math::Rect2d _bounding_rect;
    std::vector<common::math::Polyline2d> _include_polygons;
    std::vector<common::math::Polyline2d> _exclude_polygons;
};

class Crosswalk final : public PolygonFeature {
public:
    Crosswalk() = default;
    ~Crosswalk() = default;
    Crosswalk(const proto::Crosswalk& proto_corsswalk);
    
    std::string id() const;

    void setProtoCrosswalk(const proto::Crosswalk& proto_corsswalk);
    const proto::Crosswalk& getProtoCrosswalk() const;
private:
    proto::Crosswalk _proto_crosswalk;
};

class Junction final : public PolygonFeature {
public:
    Junction() = default;
    ~Junction() = default;
    Junction(const proto::Junction& proto_junction);
    
    std::string id() const;

    void setProtoJunction(const proto::Junction& proto_junction);
    const proto::Junction& getProtoJunction() const;
private:
    proto::Junction _proto_junction;
};

class ClearArea final : public PolygonFeature {
public:
    ClearArea() = default;
    ~ClearArea() = default;
    ClearArea(const proto::ClearArea& proto_clear_area);
    
    std::string id() const;

    void setProtoClearArea(const proto::ClearArea& proto_clear_area);
    const proto::ClearArea& getProtoClearArea() const;
private:
    proto::ClearArea _proto_clear_area;
};

class ParkingSpace final : public PolygonFeature {
public:
    ParkingSpace() = default;
    ~ParkingSpace() = default;
    ParkingSpace(const proto::ParkingSpace& proto_parking_space);
    
    std::string id() const;

    void setProtoParkingSpace(const proto::ParkingSpace& proto_parking_space);
    const proto::ParkingSpace& getProtoParkingSpace() const;
private:
    proto::ParkingSpace _proto_parking_space;
};

class Road final : public PolygonFeature {
public:
    Road() = default;
    ~Road() = default;
    Road(const proto::Road& proto_Road);
    
    std::string id() const;

    void setProtoRoad(const proto::Road& proto_Road);
    const proto::Road& getProtoRoad() const;
private:
    proto::Road _proto_road;
};
}
}
#endif