#ifndef _TERGEO_COMMON_MATH_TRANSFORM_H_
#define _TERGEO_COMMON_MATH_TRANSFORM_H_

#include "tergeo/common/math/point.h"
namespace tergeo {
namespace common {
namespace math {

template <typename T>
class Transform2 {
public:
    Transform2() = default;
    virtual ~Transform2() = default;

    virtual void localToGlobal(const T lx, const T ly, T& gx, T& gy) const = 0;
    virtual void globalToLocal(const T gx, const T gy, T& lx, T& ly) const = 0;
};

/**
 * X = m11 * x + m12 * y + m13
 * Y = m21 * x + m22 * y + m23
 */ 
template <typename T>
class AffineTransform2 : public Transform2<T> {
public:
    AffineTransform2() {set(1, 0, 0, 0, 1, 0);}
    virtual ~AffineTransform2() {}
    AffineTransform2(const T m11, const T m12, const T m13,
             const T m21, const T m22, const T m23) {
        set(m11, m12, m13, m21, m22, m23);
    }
    AffineTransform2(const AffineTransform2<T>& other) {*this = other;}

    void set(const T m11, const T m12, const T m13,
             const T m21, const T m22, const T m23);
    
    virtual void localToGlobal(const T lx, const T ly, T& gx, T& gy) const;
    virtual void globalToLocal(const T gx, const T gy, T& lx, T& ly) const;

    AffineTransform2<T>& operator=(const AffineTransform2<T>& other) {
        if (this == &other) {
            return *this;
        }
        for (int i = 0; i < 6; ++i) {
            this->_m[i] = other._m[i];
            this->_m_inv[i] = other._m_inv[i];
        }
        return *this;
    }
protected:
    T _m[6];
    T _m_inv[6];
};
template <typename T>
void AffineTransform2<T>::set(const T m11, const T m12, const T m13,
             const T m21, const T m22, const T m23) {
    _m[0] = m11; _m[1] = m12; _m[2] = m13;
    _m[3] = m21; _m[4] = m22; _m[5] = m23;
    T inv = 1.0 / (m11 * m22 - m21 * m12);
    _m_inv[0] = m22 * inv, _m_inv[1] = -m12 * inv;
    _m_inv[3] = -m21 * inv, _m_inv[4] = m11 * inv;
    _m_inv[2] = -(m22 * m13 - m12 * m23) * inv;
    _m_inv[5] = -(-m21 * m13 + m11 * m23) * inv;
}

template <typename T>
void AffineTransform2<T>::localToGlobal(const T lx, const T ly, T& gx, T& gy) const {
    gx = lx * _m[0] + ly * _m[1] + _m[2];
    gy = lx * _m[3] + ly * _m[4] + _m[5];
}
template <typename T>
void AffineTransform2<T>::globalToLocal(const T gx, const T gy, T& lx, T& ly) const {
    lx = _m_inv[0] * gx + _m_inv[1] * gy + _m_inv[2];
    ly = _m_inv[3] * gx + _m_inv[4] * gy + _m_inv[5];
}
using AffineTransform2f = AffineTransform2<float>;
using AffineTransform2d = AffineTransform2<double>;

}
}
}
#endif