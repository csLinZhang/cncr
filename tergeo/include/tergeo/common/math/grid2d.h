#ifndef _TERGEO_COMMON_MATH_GRID2D_H_
#define _TERGEO_COMMON_MATH_GRID2D_H_
#include <vector>
#include "tergeo/common/math/point.h"
#include "tergeo/common/math/rect.h"
#include "tergeo/common/math/algorithm.h"
namespace tergeo {
namespace common {
namespace math {

template<typename T> 
class BaseGrid2 {
public:
    BaseGrid2() = default;
    virtual ~BaseGrid2() = default;
    
    int getWidth() const {return _width;}
    int getHeight() const {return _height;}
    T getResolution() const {return _resolution;}
    T getOriginX() const {return _origin_x;}
    T getOriginY() const {return _origin_y;}

    void updateOrigin(const T origin_x, const T origin_y) {
        _origin_x = origin_x;
        _origin_y = origin_y;
    }

    void XY2xy(const T X, const T Y, int& x, int& y) const {
        x = std::round((X - _origin_x) / _resolution);
        y = std::round((Y - _origin_y) / _resolution);
    }
    void xy2XY(const int x, const int y, T& X, T& Y) const {
        X = x * _resolution + _origin_x;
        Y = y * _resolution + _origin_y;
    }
    bool isInxy(const int x, const int y) const {
        return x >= 0 && y >= 0 && x < _width && y < _height;
    }
    bool isInXY(const T X, const T Y) const {
        int x, y;
        XY2xy(X, Y, x, y);
        return isInxy(x, y);
    }
protected:
    int _width = 0;
    int _height = 0;
    T _origin_x = 0;
    T _origin_y = 0;
    T _resolution = 1;    
};

template<typename T, typename V> 
class Grid2 : public BaseGrid2<T> {
public:
    Grid2() = default;
    virtual ~Grid2() {}

    void setDefaultValue(const V default_value) {_default_value = default_value;}
    V getDefaultValue() const {return _default_value;}

    bool init(const int width, const int height, const T resolution, const V default_value);
    bool init(const Rect2<T>& rect, const T resolution, const V default_value);

    void fillByXY(const T X, const T Y, const V value);
    void fillByxy(const int x, const int y, const V value);
    V getValueByXY(const T X, const T Y) const;
    V getValueByxy(const int x, const int y) const;
    
    // note: std::vector<bool> has no member data()
    V* getData() {return _data.data();}
    const V* getData() const {return _data.data();}
    
    void fillPolygonByXY(const Polyline2<T>& polyline, const V value);
    void fillPolygonByxy(const Polyline2<T>& polyline, const V value);

    Grid2<T, V>& operator=(const Grid2<T, V>& other) {
        if (this == &other) {
            return *this;
        }
        this->_default_value = other._default_value;
        this->_data = other._data;
        this->_width = other._width;
        this->_height = other._height;
        this->_origin_x = other._origin_x;
        this->_origin_y = other._origin_y;
        this->_resolution = other._resolution;
        return *this;
    }
    void reset() {
        std::fill(_data.begin(), _data.end(), _default_value);
    }
    void reset(const int width, const int height) {
        if (width * height < 0) {
            return;
        }
        this->_width = width;
        this->_height = height;
        _data.resize(width * height);
        reset();
    }
protected:
    V _default_value;
    std::vector<V> _data;
};
template<typename T, typename V> 
bool Grid2<T, V>::init(const int width, const int height, 
        const T resolution, const V default_value) {
    _default_value = default_value;
    this->_resolution = resolution;
    this->_width = width;
    this->_height = height;
    _data.clear();
    if (width * height < 0) {
        return false;
    }
    _data.resize(width * height, _default_value);
    return true;
}
template<typename T, typename V> 
bool Grid2<T, V>::init(const Rect2<T>& rect, 
        const T resolution, const V default_value) {
    this->_origin_x = rect.min_x;
    this->_origin_y = rect.min_y;
    int width = static_cast<int>(rect.width() / resolution + 1);
    int height = static_cast<int>(rect.height() / resolution + 1);
    return Grid2<T, V>::init(width, height, resolution, default_value);
}
template<typename T, typename V>
void Grid2<T, V>::fillByXY(const T X, const T Y, const V value) {
    int x, y;
    BaseGrid2<T>::XY2xy(X, Y, x, y);
    fillByxy(x, y, value);
}
template<typename T, typename V>
void Grid2<T, V>::fillByxy(const int x, const int y, const V value) {
    if (!BaseGrid2<T>::isInxy(x, y)) {
        return;
    }
    _data[y * this->_width + x] = value;
}
template<typename T, typename V>
V Grid2<T, V>::getValueByXY(const T X, const T Y) const {
    int x, y;
    BaseGrid2<T>::XY2xy(X, Y, x, y);
    return getValueByxy(x, y);
}
template<typename T, typename V>
V Grid2<T, V>::getValueByxy(const int x, const int y) const {
    if (!BaseGrid2<T>::isInxy(x, y)) {
        return _default_value;
    }
    return _data[y * this->_width + x];
}
template<typename T, typename V>
void Grid2<T, V>::fillPolygonByXY(const Polyline2<T>& polyline, const V value) {
    Polyline2<T> polyline_xy(polyline.size());
    for (int i = 0; i < polyline.size(); ++i) {
        polyline_xy[i].x = (polyline[i].x - this->_origin_x) / this->_resolution;
        polyline_xy[i].y = (polyline[i].y - this->_origin_y) / this->_resolution;
    }
    fillPolygonByxy(polyline_xy, value);
}
template<typename T, typename V>
void Grid2<T, V>::fillPolygonByxy(const Polyline2<T>& polyline, const V value) {
    Polyline2<T> points;
    FindPointsInPolygon(polyline, points);
    for (auto& point : points) {
        fillByxy(std::round(point.x), std::round(point.y), value);
    }
}

}    
}
}
#endif

