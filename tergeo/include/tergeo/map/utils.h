#ifndef _TERGEO_MAP_UTILS_H_
#define _TERGEO_MAP_UTILS_H_
#include "tergeo/common/math/point.h"

namespace tergeo {
namespace map {

void SamplingLine(const common::math::Point2d& start_point, 
        const common::math::Point2d& end_point,
        common::math::Polyline2d& polyline,
        const double step = 1.0, const bool with_end = true);
            
void SamplingPolyline(const common::math::Polyline2d& polyline_in, 
        common::math::Polyline2d& polyline_out,
        const double step = 1.0);
}
}
#endif