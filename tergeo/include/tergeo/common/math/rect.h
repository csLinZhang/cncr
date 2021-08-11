#ifndef _TERGEO_COMMON_MATH_RECT_H_
#define _TERGEO_COMMON_MATH_RECT_H_
#include <math.h>
#include <vector>
#include <limits>
#include "tergeo/common/math/point.h"
namespace tergeo {
namespace common {
namespace math {
template<typename T>
struct Rect2 {
    Rect2() : min_x(std::numeric_limits<T>::max()), 
        max_x(std::numeric_limits<T>::lowest()), 
        min_y(std::numeric_limits<T>::max()), 
        max_y(std::numeric_limits<T>::lowest()) {}
    Rect2(T min_x_, T max_x_, T min_y_, T max_y_) : 
        min_x(min_x_), max_x(max_x_), min_y(min_y_), max_y(max_y_) {}
    Rect2(const Rect2<T>& other) : 
        min_x(other.min_x), max_x(other.max_x), min_y(other.min_y), max_y(other.max_y) {}
    T min_x;
    T max_x;
    T min_y;
    T max_y;
    T width() const {return max_x - min_x;}
    T height() const {return max_y - min_y;}  
    Point2<T> center() const {
        return Point2<T>((min_x + max_x) * 0.5, (min_y + max_y) * 0.5);
    } 
    Rect2<T>& operator=(const Rect2<T>& other) {
        if (this == &other) {
            return *this;
        }
        this->min_x = other.min_x;
        this->max_x = other.max_x;
        this->min_y = other.min_y;
        this->max_y = other.max_y;
        return *this;
    }
    bool isIn(const T x, const T y) const {
        return x >= min_x && x <= max_x 
            && y >= min_y && y <= max_y;
    }
};
typedef Rect2<double> Rect2d;
typedef Rect2<float> Rect2f;
typedef Rect2<int> Rect2i;

template<typename T>
Rect2<T> UnionRect(const Rect2<T>& rect_1, const Rect2<T>& rect_2) {
    return Rect2<T>(std::min(rect_1.min_x, rect_2.min_x),
                    std::max(rect_1.max_x, rect_2.max_x),
                    std::min(rect_1.min_y, rect_2.min_y),
                    std::max(rect_1.max_y, rect_2.max_y));
}

template<typename T>
class BoundingRect2 {
public:
    BoundingRect2() = default;
    virtual ~BoundingRect2() = default;
    explicit BoundingRect2(const Polyline2<T>& points);
    BoundingRect2(const BoundingRect2<T>& other);
    const Rect2<T>& getRect() const {return _rect;}

    void fitPoint(const T x, const T y);
    void fitPoint(const Point2<T>& point);
    void fitPoints(const Polyline2<T>& points);
    BoundingRect2<T>& operator=(const BoundingRect2<T>& other);
    
    bool isIn(const T x, const T y) const;
    bool isIn(const Point2<T>& point) const;
protected:
    Rect2<T> _rect;
};
template<typename T>
BoundingRect2<T>::BoundingRect2(const Polyline2<T>& points) {
    fitPoints(points);
}
template<typename T>
BoundingRect2<T>::BoundingRect2(const BoundingRect2<T>& other) : _rect(other._rect) {}

template<typename T>
void BoundingRect2<T>::fitPoint(const T x, const T y) {
    if (x < _rect.min_x) {_rect.min_x = x - s_epsilon;}
    if (x > _rect.max_x) {_rect.max_x = x + s_epsilon;}
    if (y < _rect.min_y) {_rect.min_y = y - s_epsilon;}
    if (y > _rect.max_y) {_rect.max_y = y + s_epsilon;}
}
template<typename T>
void BoundingRect2<T>::fitPoint(const Point2<T>& point) {
    fitPoint(point.x, point.y);
}
template<typename T>
void BoundingRect2<T>::fitPoints(const Polyline2<T>& points) {
    for (const auto& point : points) {
        fitPoint(point.x, point.y);
    }
}
template<typename T>
BoundingRect2<T>& BoundingRect2<T>::operator=(const BoundingRect2<T>& other) {
    if (this == &other) {
        return *this;
    }
    this->_rect = other._rect;
    return *this;
}
template<typename T>
bool BoundingRect2<T>::isIn(const T x, const T y) const {
    return _rect.isIn(x, y);
}
template<typename T>
bool BoundingRect2<T>::isIn(const Point2<T>& point) const {
    return _rect.isIn(point.x, point.y);
}

}
}
}
#endif