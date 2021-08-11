#ifndef _TERGEO_COMMON_MATH_POINT_H_
#define _TERGEO_COMMON_MATH_POINT_H_
#include <cmath>
#include <vector>
#include <limits>

namespace tergeo {
namespace common {
namespace math {

const double s_epsilon = 1e-6;

template<typename T>
struct Point2 {
    Point2() : x(0), y(0) {}
    Point2(T x_, T y_) : x(x_), y(y_) {}
    Point2(const Point2<T>& other) : x(other.x), y(other.y) {}
    T x;
    T y;
    
    bool operator==(const Point2<T> &other) const {
        return other.x == x && other.y == y; 
    }
    bool operator!=(const Point2<T> &other) const {
        return !(other == *this);
    }
    Point2<T>& operator=(const Point2<T>& other) {
        if (this == &other) {
            return *this;
        }
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
};

using Point2i = Point2<int>;
using Point2f = Point2<float>;
using Point2d = Point2<double>;

template <typename T>
using Polyline2 = std::vector<Point2<T>>;
using Polyline2i = Polyline2<int>;
using Polyline2f = Polyline2<float>;
using Polyline2d = Polyline2<double>;

template<typename T>
struct Point3 {
    Point3() : x(0), y(0), z(0) {}
    Point3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
    Point3(const Point3<T>& other) : x(other.x), y(other.y), z(other.z) {}
    T x;
    T y;
    T z;
    bool operator==(const Point2<T> &other) const {
        return other.x == x && other.y == y && other.z == z; 
    }
    bool operator!=(const Point2<T> &other) const {
        return !(other == *this);
    }
    Point3<T>& operator=(const Point3<T>& other) {
        if (this == &other) {
            return *this;
        }
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }
};

using Point3i = Point3<int>;
using Point3f = Point3<float>;
using Point3d = Point3<double>;

using Point3iList = std::vector<Point3i>;
using Point3fList = std::vector<Point3f>;
using Point3dList = std::vector<Point3d>;

template <typename T>
using Polyline3 = std::vector<Point3<T>>;
using Polyline3i = Polyline3<int>;
using Polyline3f = Polyline3<float>;
using Polyline3d = Polyline3<double>;

template<typename T>
T PointToPointSquare(const Point2<T>& pt_1, const Point2<T>& pt_2) {
    return (pt_1.x - pt_2.x) * (pt_1.x - pt_2.x) 
        + (pt_1.y - pt_2.y) * (pt_1.y - pt_2.y);
}
template<typename T>
T PointToPoint(const Point2<T>& pt_1, const Point2<T>& pt_2) {
    return std::hypot(pt_1.x - pt_2.x, pt_1.y - pt_2.y);
}
template<typename T>
T PointToPointSquare(const Point3<T>& pt_1, const Point3<T>& pt_2) {
    return (pt_1.x - pt_2.x) * (pt_1.x - pt_2.x) 
        + (pt_1.y - pt_2.y) * (pt_1.y - pt_2.y) 
        + (pt_1.z - pt_2.z) * (pt_1.z - pt_2.z);
}
template<typename T>
T PointToPoint(const Point3<T>& pt_1, const Point3<T>& pt_2) {
    return std::sqrt(PointToPointSquare(pt_1, pt_2));
}

}
}
}

#endif