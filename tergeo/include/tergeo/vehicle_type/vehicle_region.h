#ifndef _TERGEO_VEHICLE_TYPE_VEHICLE_REGION_H
#define _TERGEO_VEHICLE_TYPE_VEHICLE_REGION_H

#include <string>
#include <vector>
#include "tergeo/common/macro.h"
#include "tergeo/common/math/grid2d.h"
#include "tergeo/vehicle_type/proto/vehicle_type.pb.h"
namespace tergeo {
namespace vehicle_type {

class VehicleRegion {
public:
    VehicleRegion() = default;
    virtual ~VehicleRegion() = default;
    
    void setProtoVehicleRegion(const proto::VehicleRegion& vehicle_region);
    const proto::VehicleRegion& getProtoVehicleRegion() const;
    const std::vector<common::math::Polyline2f>& getIncludePolygons() const;
    const std::vector<common::math::Polyline2f>& getExcludePolygons() const;

    bool isIn(const float x, const float y) const;
    bool isIn(const common::math::Point2f& point) const;
private:
    std::vector<common::math::Polyline2f> _include_polygons;
    std::vector<common::math::Polyline2f> _exclude_polygons;
    proto::VehicleRegion _vehicle_region;
    common::math::Grid2<float, bool> _grid;
};
}
}
#endif