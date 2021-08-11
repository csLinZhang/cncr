#ifndef _TERGEO_PLANNING_UTILS_H
#define _TERGEO_PLANNING_UTILS_H
#include "tergeo/common/common.hpp"

namespace tergeo {
namespace planning {

struct VehicleState {
    double speed_mps;
    double omega_radps;
};

struct Obstacle {
    int id;
    int type;
    common::math::Point3d center;
    common::math::Point3dList points;
    common::math::Box3d box;
    common::math::Polyline3d polygon;
};

struct Pose2dVT {
    tergeo::common::math::Pose2d pose;
    double velocity;
    double relative_time;
};

using TCMPose2d = tergeo::common::math::Pose2d;
using TCMPose2f = tergeo::common::math::Pose2f;
using TCMPoint2f = tergeo::common::math::Point2f;
using TCMPoint2d = tergeo::common::math::Point2d;
using TCMPoint2dVec = std::vector<TCMPoint2d>;
using TCMPose2dVec = std::vector<TCMPose2d>;

using Trajectory = std::vector<Pose2dVT>;
using ObstacleList = std::vector<Obstacle>;
}
}

#endif