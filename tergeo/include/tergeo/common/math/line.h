#ifndef _TERGEO_COMMON_MATH_LINE_H_
#define _TERGEO_COMMON_MATH_LINE_H_
#include "tergeo/common/math/point.h"

namespace tergeo {
namespace common {
namespace math {

template <typename T>
struct Line2 {
    Line2() = default;
    Line2(const Point2<T>& start, const Point2<T>& end) : 
        start_point(start), end_point(end) {}
    Point2<T> start_point;
    Point2<T> end_point;
    
    Point2<T> Direction() const;
    Point2<T> Normal() const;
};

template <typename T>
Point2<T> Line2<T>::Direction() const {
    T dx = start_point.x - end_point.x;
    T dy = start_point.y - end_point.y;
    T d = std::hypot(dx, dy);
    if (std::fabs(d) < s_epsilon) {
        return Point2<T>(0, 0);
    } else {
        return Point2<T>(dx / d, dy / d);
    }
}
template <typename T>
Point2<T> Line2<T>::Normal() const {
    T dx = start_point.x - end_point.x;
    T dy = start_point.y - end_point.y;
    T d = std::hypot(dx, dy);
    if (std::fabs(d) < s_epsilon) {
        return Point2<T>(0, 0);
    } else {
        return Point2<T>(dy / d, -dx / d);
    }
}

template<typename T>
double PointToLine(const Point2<T>& pt, 
        const Point2<T>& line_pt_1, const Point2<T>& line_pt_2) {
    T dx = line_pt_2.x - line_pt_1.x;
    T dy = line_pt_2.y - line_pt_1.y;
    T d = std::hypot(dx, dy);
    if (d < s_epsilon) {
        return PointToPoint(pt, line_pt_1);
    }
    return std::fabs((dy * (pt.x - line_pt_1.x) 
        - dx * (pt.y - line_pt_1.x)) / d);
}

template<typename T>
double PointToLine(const Point2<T>& pt, const Line2<T>& line) {
    return PointToLine(pt, line.start_point, line.end_point);
}

}
}
}
#endif