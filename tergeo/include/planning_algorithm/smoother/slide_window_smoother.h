#ifndef _TERGEO_PLANNING_ALGORITHM_SLIDE_WINDOW_SMOOTHER_H_
#define _TERGEO_PLANNING_ALGORITHM_SLIDE_WINDOW_SMOOTHER_H_
#pragma once
#include <vector>
#include <cmath>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>

namespace tergeo {
namespace planning {
namespace algorithm {
class SlideWindowSmoother{
public:
    SlideWindowSmoother(){}
    ~SlideWindowSmoother(){}
    void smooth(const Eigen::Matrix<double, Eigen::Dynamic, 2>& pts,
                Eigen::Matrix<double, Eigen::Dynamic, 2>& smoothed_pts,
                int window_size = 11); 
private:
    void fitLine(const Eigen::Matrix<double, Eigen::Dynamic, 2>& pts,
                Eigen::Vector3d& line_coeff);
};

}
}
}

#endif