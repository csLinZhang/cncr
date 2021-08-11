#ifndef _TERGEO_MAP_RASTER_H
#define _TERGEO_MAP_RASTER_H
#include "tergeo/common/common.hpp"
#include "tergeo/common/math/transform.h"
#include <opencv2/core.hpp>

namespace tergeo {
namespace map {

class Raster {
public:
    DECLARE_SHARED_PTR(Raster)
    Raster() = default;
    virtual ~Raster() = default;
    
    bool load(const std::string filename);
    
    std::string getName() const {return _name;}
    const cv::Mat& getImage() const {return _image;}
    int getWidth() const {return _image.cols;}
    int getHeight() const {return _image.rows;}

    void XY2xy(const double X, const double Y, int& x, int& y) const;
    void xy2XY(const int x, const int y, double& X, double& Y) const;

    bool isPointIn(const double X, const double Y) const;
    double distance(const double X, const double Y) const;

    const common::math::Rect2d& getBoundingRect() const {return _bounding_rect;}
    Raster& operator=(const Raster& other);
    
    //////
    static int Load(const std::string map_path = "");
    static const Raster* GetRaster(const std::string name);
    static const Raster* GetRaster(const double X, const double Y);
    static std::vector<std::string> getRasterNames();
private:
    cv::Mat _image;
    std::string _name;
    common::math::Rect2d _bounding_rect;
    common::math::AffineTransform2d _affine_transform;
};
}
}
#endif