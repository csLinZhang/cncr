#ifndef _TERGEO_COMMON_BOUNDING_BOX_H_
#define _TERGEO_COMMON_BOUNDING_BOX_H_

#include "tergeo/common/math/point.h"
namespace tergeo {
namespace common {
namespace math {
template<typename T>
struct Box3 {
    Box3() : min_x(std::numeric_limits<T>::max()), 
        max_x(std::numeric_limits<T>::lowest()), 
        min_y(std::numeric_limits<T>::max()), 
        max_y(std::numeric_limits<T>::lowest()),
        min_z(std::numeric_limits<T>::max()), 
        max_z(std::numeric_limits<T>::lowest()) {}
    Box3(T min_x_, T max_x_, T min_y_, T max_y_, T min_z_, T max_z_) : 
        min_x(min_x_), max_x(max_x_), min_y(min_y_), 
        max_y(max_y_), min_z(min_z_), max_z(max_z_) {}
    Box3(const Rect2<T>& other) : 
        min_x(other.min_x), max_x(other.max_x), min_y(other.min_y), 
        max_y(other.max_y), min_z(other.min_z), max_z(other.max_z) {}
    T min_x;
    T max_x;
    T min_y;
    T max_y;
    T min_z;
    T max_z;
    T length() const {return max_x - min_x;}
    T width() const {return max_y - min_y;}
    T height() const {return max_z - min_z;}  
    Point3<T> center() const {
        return Point3<T>((min_x + max_x) * 0.5, 
                         (min_y + max_y) * 0.5,
                         (min_z + max_z) * 0.5);
    } 
    Box3<T>& operator=(const Box3<T>& other) {
        if (this == &other) {
            return *this;
        }
        this->min_x = other.min_x;
        this->max_x = other.max_x;
        this->min_y = other.min_y;
        this->max_y = other.max_y;
        this->min_z = other.min_z;
        this->max_z = other.max_z;
        return *this;
    }
    bool isIn(const T x, const T y, const T z) const {
        return x >= min_x && x <= max_x 
            && y >= min_y && y <= max_y
            && z >= min_z && z <= max_z;
    } 
};
typedef Box3<double> Box3d;
typedef Box3<float> Box3f;
typedef Box3<int> Box3i;
template<typename T>
Box3<T> UnionBox(const Box3<T>& rect_1, const Box3<T>& rect_2) {
    return Box3<T>(std::min(rect_1.min_x, rect_2.min_x),
                   std::max(rect_1.max_x, rect_2.max_x),
                   std::min(rect_1.min_y, rect_2.min_y),
                   std::max(rect_1.max_y, rect_2.max_y),
                   std::min(rect_1.min_z, rect_2.min_z),
                   std::max(rect_1.max_z, rect_2.max_z));
}


template<typename T>
class BoundingBox3 {
public:
    BoundingBox3() = default;
    virtual ~BoundingBox3() = default;
    explicit BoundingBox3(const Polyline3<T>& points);
    BoundingBox3(const BoundingBox3<T>& other);
    const BoundingBox3<T>& getBox() const {return _box;}

    void fitPoint(const T x, const T y, const T z);
    void fitPoint(const Point3<T>& point);
    void fitPoints(const Polyline3<T>& points);
    BoundingBox3<T>& operator=(const BoundingBox3<T>& other);
    
    bool isIn(const T x, const T y, const T z) const;
    bool isIn(const Point3<T>& point) const;
protected:
    Box3<T> _box;
};
template<typename T>
BoundingBox3<T>::BoundingBox3(const Polyline3<T>& points) {
    fitPoints(points);
}
template<typename T>
BoundingBox3<T>::BoundingBox3(const BoundingBox3& other) : _box(other._box) {}

template<typename T>
void BoundingBox3<T>::fitPoint(const T x, const T y, const T z) {
    if (x < _box.min_x) {_box.min_x = x - s_epsilon;}
    if (x > _box.max_x) {_box.max_x = x + s_epsilon;}
    if (y < _box.min_y) {_box.min_y = y - s_epsilon;}
    if (y > _box.max_y) {_box.max_y = y + s_epsilon;}
    if (z < _box.min_z) {_box.min_z = z - s_epsilon;}
    if (z > _box.max_z) {_box.max_z = z + s_epsilon;}
}
template<typename T>
void BoundingBox3<T>::fitPoint(const Point3<T>& point) {
    fitPoint(point.x, point.y, point.z);
}
template<typename T>
void BoundingBox3<T>::fitPoints(const Polyline3<T>& points) {
    for (const auto& point : points) {
        fitPoint(point.x, point.y, point.z);
    }
}
template<typename T>
BoundingBox3<T>& BoundingBox3<T>::operator=(const BoundingBox3<T>& other) {
    if (this == &other) {
        return *this;
    }
    this->_box = other._box;
    return *this;
}
template<typename T>
bool BoundingBox3<T>::isIn(const T x, const T y, const T z) const {
    return _box.isIn(x, y, z);
}
template<typename T>
bool BoundingBox3<T>::isIn(const Point3<T>& point) const {
    return _box.isIn(point.x, point.y, point.z);
}

}
}
}

#endif