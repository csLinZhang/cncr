/**
 * @file eigen_utils.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief eigen基础函数
 */
#ifndef _TERGEO_COMMON_EIGEN_UTILS_H_
#define _TERGEO_COMMON_EIGEN_UTILS_H_
#include <Eigen/Core>
#include <Eigen/Dense>
namespace tergeo {
namespace common {
namespace eigen {
template <typename T>
Eigen::Matrix<T, 3, 3> AxisToRotation(const Eigen::Matrix<T, 3, 1>& rvec) {
	T angle = rvec.norm();
	if (std::fabs(angle) < 1e-6) {
		return Eigen::Matrix<T, 3, 3>::Identity();
	}
	Eigen::Matrix<T, 3, 1> axis; axis = rvec.normalized();
    //T cost = std::cos(angle);
    //T sint = std::sin(angle);
    //Eigen::Matrix<T, 3, 1> cos_vec = (1 - cost) * axis;
    //Eigen::Matrix<T, 3, 1> sin_vec = sint * axis;
    //Eigen::Matrix<T, 3, 3> p = cos_vec * axis.transpose();
    //p(0, 0) += cost;       p(0, 1) -= sin_vec(2); p(0, 2) += sin_vec(1);
    //p(1, 0) += sin_vec(2); p(1, 1) += cost;       p(1, 2) -= sin_vec(0);
    //p(2, 0) -= sin_vec(1); p(2, 1) += sin_vec(0); p(2, 2) += cost;
    //return p;
	Eigen::Matrix<T, 3, 3> rot; rot = Eigen::AngleAxis<T>(angle, axis);
    return rot;
}

template <typename T>
Eigen::Matrix<T, 3, 1> RotationToAxis(const Eigen::Matrix<T, 3, 3>& rot) {
    //Eigen::Matrix<T, 3, 1> a; a << 
    //    rot(2, 1) - rot(1, 2), 
    //    rot(0, 2) - rot(2, 0), 
    //    rot(1, 0) - rot(0, 1);
    //return std::asin(a.norm() * 0.5) * a.normalized();
    Eigen::AngleAxis<T> angle_axis; angle_axis.fromRotationMatrix(rot);
    return angle_axis.angle() * angle_axis.axis();
}

template <typename T> // euler : roll pitch yaw
Eigen::Matrix<T, 3, 3> RPYToRotation(const Eigen::Matrix<T, 3, 1>& euler) {
    T cx = std::cos(euler(0)), sx = std::sin(euler(0));
    T cy = std::cos(euler(1)), sy = std::sin(euler(1));
    T cz = std::cos(euler(2)), sz = std::sin(euler(2));
    return (Eigen::Matrix<T, 3, 3>() << 
        cz * cy, -sz * cx + cz * sy * sx, sz * sx + cz * sy * cx,
        sz * cy, cz * cx + sz * sy * sx, -cz * sx + sz * sy * cx,
        -sy, cy * sx, cy * cx).finished();
}
template <typename T> // euler : roll pitch yaw
Eigen::Matrix<T, 3, 1> RPYToAxis(const Eigen::Matrix<T, 3, 1>& euler) {
    return RotationToAxis(RPYToRotation(euler));
}
template <typename T> // euler : roll pitch yaw
Eigen::Matrix<T, 3, 1> RotationToRPY(const Eigen::Matrix<T, 3, 3>& rot) {
    if (std::fabs(std::fabs(double(rot(2, 0))) - 1.0) < 1e-6) {
        if (rot(2, 0) > T(0)) {
            return (Eigen::Matrix<T, 3, 1>() << 
            T(0), 
            T(std::asin(-1.0)),
            T(std::atan2(-rot(0, 1), -rot(0, 2)))).finished();
        } else {
            return (Eigen::Matrix<T, 3, 1>() << 
            T(0), 
            T(std::asin(1.0)),
            T(-std::atan2(rot(0, 1), rot(0, 2)))).finished();
        }
    } else {
        return (Eigen::Matrix<T, 3, 1>() <<
        	T(std::atan2(rot(2, 1), rot(2, 2))),
        	T(std::atan2(-rot(2, 0), std::sqrt(rot(2, 1) * rot(2, 1) + rot(2, 2) * rot(2, 2)))),
        	T(std::atan2(rot(1, 0), rot(0, 0)))).finished();
    }
}
template <typename T> // euler : roll pitch yaw
Eigen::Matrix<T, 3, 1> AxisToRPY(const Eigen::Matrix<T, 3, 1>& axis) {
    return RotationToRPY(AxisToRotation(axis));
}
template<typename T> // quat: w, x, y, z
Eigen::Matrix<T, 4, 1> AxisToQuaternion(const Eigen::Matrix<T, 3, 1>& rvec) {
	Eigen::Matrix<T, 3, 3> rmat = AxisToRotation<T>(rvec);
	Eigen::Quaternion<T> quat(rmat);
    return (Eigen::Matrix<T, 4, 1>() << quat.w(), quat.x(), quat.y(), quat.z()).finished();
}
template<typename T> // quat: w, x, y, z
Eigen::Matrix<T, 4, 1> RotationToQuaternion(const Eigen::Matrix<T, 3, 3>& rot) {
    //T w = std::sqrt(1.0 + rot(0, 0) + rot(1, 1) + rot(2, 2)) * 0.5;
    //T x = (rot(2, 1) - rot(1, 2)) / (4 * w);
    //T y = (rot(0, 2) - rot(2, 0)) / (4 * w);
    //T z = (rot(1, 0) - rot(0, 1)) / (4 * w);
    //return (Eigen::Matrix<T, 4, 1>() << w, x, y, z).finished();
	Eigen::Quaternion<T> quat(rot);
    return (Eigen::Matrix<T, 4, 1>() << quat.w(), quat.x(), quat.y(), quat.z()).finished();
}
template<typename T> // quat: w, x, y, z
Eigen::Matrix<T, 3, 3> QuaternionToRotation(const T w, const T x, const T y, const T z) {
    //return (Eigen::Matrix<T, 3, 3>() << 
    //    2 * (w * w + x * x) - 1, 2 * (x * y - w * z), 2 * (x * z + w * y),
    //    2 * (x * y + w * z), 2 * (w * w + y * y) - 1, 2 * (y * z - w * x),
    //    2 * (x * z - w * y), 2 * (y * z + w * x), 2 * (w * w + z * z) - 1).finished();
    Eigen::Quaternion<T> quat(w, x, y, z);
    return quat.toRotationMatrix();
}
template<typename T> // quat: w, x, y, z
Eigen::Matrix<T, 3, 3> QuaternionToRotation(const Eigen::Matrix<T, 4, 1>& q) {
    return QuaternionToRotation(q(0), q(1), q(2), q(3));
}

template<typename T>
Eigen::Matrix<T, 3, 1> QuaternionToAxis(const Eigen::Matrix<T, 4, 1>& q) {
	Eigen::Quaternion<T> quat(q(0), q(1), q(2), q(3));
	return RotationToAxis(quat.toRotationMatrix());
}
template<typename T>
Eigen::Matrix<T, 3, 1> QuaternionToRPY(const Eigen::Matrix<T, 4, 1>& q) {
	Eigen::Quaternion<T> quat(q(0), q(1), q(2), q(3));
	return RotationToRPY(quat.toRotationMatrix());
}

template<typename T>
void MatrixToExtrinsic(const Eigen::Matrix<T, 4, 4>& matrix, T extrinsic[6]) {
    Eigen::Matrix<T, 3, 3> rot = matrix.block(0, 0, 3, 3);
    Eigen::Matrix<T, 3, 1> rvec = RotationToAxis(rot);
    extrinsic[0] = rvec(0); 
    extrinsic[1] = rvec(1); 
    extrinsic[2] = rvec(2);
    extrinsic[3] = matrix(0, 3);
    extrinsic[4] = matrix(1, 3); 
    extrinsic[5] = matrix(2, 3);
}
template<typename T>
void ExtrinsicToMatrix(const T extrinsic[6], Eigen::Matrix<T, 4, 4>& matrix) {
    Eigen::Matrix<T, 3, 1> rvec; rvec << extrinsic[0], extrinsic[1], extrinsic[2];
    matrix.setIdentity();
    Eigen::Matrix<T, 3, 3> rot = AxisToRotation(rvec);
    matrix.block(0, 0, 3, 3) = rot;
    matrix(0, 3) = extrinsic[3];
    matrix(1, 3) = extrinsic[4];
    matrix(2, 3) = extrinsic[5];
}
template<typename T>
void InverseExtrinsic(const T extrinsic[6], T extrinsic_inv[6]) {
    Eigen::Matrix<T, 3, 1> rvec, tvec;
    rvec << -extrinsic[0], -extrinsic[1], -extrinsic[2];
    tvec << extrinsic[3], extrinsic[4], extrinsic[5];
    Eigen::Matrix<T, 3, 3> rot = AxisToRotation(rvec);
    Eigen::Matrix<T, 3, 1> tvec_inv = -rot * tvec;
    extrinsic_inv[0] = rvec[0];
    extrinsic_inv[1] = rvec[1];
    extrinsic_inv[2] = rvec[2];
    extrinsic_inv[3] = tvec_inv(0);
    extrinsic_inv[4] = tvec_inv(1);
    extrinsic_inv[5] = tvec_inv(2);
}
}
}
}

#endif