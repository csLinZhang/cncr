#ifndef _TERGEO_COMMON_MATH_POSE_H
#define _TERGEO_COMMON_MATH_POSE_H
#include <Eigen/Dense>
#include <Eigen/Core>
namespace tergeo {
namespace common {
namespace math {
template<typename T>
struct Pose2 {
    Pose2() : x(0), y(0), theta(0) {}
    Pose2(T x_, T y_, T theta_) : x(x_), y(y_), theta(theta_) {}
    Pose2(const Pose2<T>& other) {*this = other;}
    T x;
    T y;
    T theta;

    Pose2<T>& operator=(const Pose2<T>& other) {
        if (this == &other) {
            return *this;
        }
        this->x = other.x;
        this->y = other.y;
        this->theta = other.theta;
        return *this;
    }
    Eigen::Matrix<T, 3, 3> toMatrix() const {
        T ct = std::cos(theta);
        T st = std::sin(theta);
        return (Eigen::Matrix<T, 3, 3>() << 
            ct, -st, x,
            st, ct, y,
            0, 0, 1).finished();
    }
};

using Pose2f = Pose2<float>;
using Pose2d = Pose2<double>;

using Pose2dList = std::vector<Pose2d>;
using Pose2fList = std::vector<Pose2f>;

template<typename T>
struct Pose3 {
    Pose3() : x(0), y(0), z(0), qw(1.0), qx(0), qy(0), qz(0) {}
    Pose3(T x_, T y_, T z_, T qw_, T qx_, T qy_, T qz_) : 
        x(x_), y(y_), z(z_), qw(qw_), qx(qx_), qy(qy_), qz(qz_) {}
    Pose3(const Pose3<T>& other) {*this = other;}
    T x;
    T y;
    T z;
    T qw;
    T qx;
    T qy;
    T qz;

    Pose3<T>& operator=(const Pose3<T>& other) {
        if (this == &other) {
            return *this;
        }
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->qw = other.qw;
        this->qx = other.qx;
        this->qy = other.qy;
        this->qz = other.qz;
        return *this;
    }
    Eigen::Matrix<T, 4, 4> toMatrix() const {
        Eigen::Quaternion<T> quat(qw, qx, qy, qz);
        Eigen::Matrix<T, 3, 3> rot = quat.toRotationMatrix();
        return (Eigen::Matrix<T, 4, 4>() << 
            rot(0, 0), rot(0, 1), rot(0, 2), x,
            rot(1, 0), rot(1, 1), rot(1, 2), y,
            rot(2, 0), rot(2, 1), rot(2, 2), z,
            0, 0, 0 , 1).finished();
    }
    void fromMatrix(const Eigen::Matrix<T, 4, 4>& matrix) {
        Eigen::Matrix<T, 3, 3> rot; rot = matrix.block(0, 0, 3, 3);
        Eigen::Quaternion<T> quat(rot);
        this->x = matrix(0, 3);
        this->y = matrix(1, 3);
        this->z = matrix(2, 3);
        this->qw = quat.w();
        this->qx = quat.x();
        this->qy = quat.y();
        this->qz = quat.z();
    }
};

using Pose3f = Pose3<float>;
using Pose3d = Pose3<double>;
using Pose3dList = std::vector<Pose3d>;
using Pose3fList = std::vector<Pose3f>;
}
}
}

#endif