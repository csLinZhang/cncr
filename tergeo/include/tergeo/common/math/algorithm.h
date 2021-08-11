#ifndef _TERGEO_COMMON_MATH_ALGORITHM_H_
#define _TERGEO_COMMON_MATH_ALGORITHM_H_
#include <cmath>
#include <vector>
#include <algorithm>
#include "tergeo/common/math/point.h"
#include "tergeo/common/math/rect.h"

namespace tergeo {
namespace common {
namespace math {

template<typename T>
bool isConvexPolygon(const std::vector<Point2<T> >& polygon) {
    if (polygon.size() < 4) {
        return true;
    }
    int pt_num_1 = polygon.size() - 1;
    T dx1, dy1, dx2, dy2, v1 = 0, v2;
    for (int i = 0, j = pt_num_1; i < pt_num_1; j = i++) {
        dx1 = polygon[i].x - polygon[j].x;
        dy1 = polygon[i].y - polygon[j].y;
        dx2 = polygon[i + 1].x - polygon[i].x;
        dy2 = polygon[i + 1].y - polygon[i].y;
        v2 = dx1 * dy2 - dx2 * dy1;
        if (i > 0 && v1 * v2 < 0) {
            return false;
        }
        if (std::fabs(v2) > 1e-6){
            v1 = v2;
        }
    }
    return true;
}
template<typename T>
bool PointInPolygon(const Point2<T>& pt, 
        const std::vector<Point2<T> >& polygon) {
    int pt_num = polygon.size();
    if (pt_num < 3) {
        return false;
    }
    bool flag = false;
    for (int i = 0, j = pt_num - 1; i < pt_num; j = i++) {
        if (bool(polygon[i].x > pt.x) == bool(polygon[j].x > pt.x)) {
            continue;
        }
        T y = (polygon[j].y - polygon[i].y) * (pt.x - polygon[i].x)
                / (polygon[j].x - polygon[i].x) + polygon[i].y;
        if (y <= pt.y) {
            continue;
        }
        flag = !flag;
    }
    return flag;
}
template<typename T>
void FindPointsInPolygon(const std::vector<Point2<T> >& polygon, 
        std::vector<Point2<T> >& points) {
    points.clear();
    int pt_num = polygon.size();
    if (pt_num < 3) {
        return;
    }
    BoundingRect2<T> bb(polygon);
    const Rect2<T>& rect = bb.getRect();
    T min_x = std::floor(rect.min_x);
    T max_x = std::ceil(rect.max_x);
    std::vector<T> y_vec;
    for (T x = min_x; x < max_x; x += 1.0) {
        y_vec.clear();
        for (int i = 0, j = pt_num -1; i < pt_num; j = i++) {
            if (bool(polygon[i].x > x) == bool(polygon[j].x > x)) {
                continue;
            }
            T y = (polygon[j].y - polygon[i].y) * (x - polygon[i].x)
                / (polygon[j].x - polygon[i].x) + polygon[i].y;
            if (y < rect.min_y || y > rect.max_y) {
                continue;
            }
            y_vec.emplace_back(y);
        }
        if (y_vec.size() % 2 != 0) {
            continue;
        }
        std::sort(y_vec.begin(), y_vec.end());
        for (int i = 0; i < y_vec.size(); i += 2) {
            for (T y = std::ceil(y_vec[i]); y <= y_vec[i + 1]; y += 1) {
                points.push_back(Point2<T>(x, y));
            }
        }
    }
}

}
}
}
#endif