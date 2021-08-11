#ifndef _BASE_COVERAGE_PLANNER_H
#define _BASE_COVERAGE_PLANNER_H

#include <vector>
#include <string>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>

namespace tergeo{
namespace planning{
namespace algorithm{

struct Point{
    public:
    Point():x(0.0), y(0.0){}
    Point(double x_, double y_):x(x_),y(y_){}
    double x, y;
};

struct Pose{
    Point position;
    double heading;
};

struct  Trajectory{
    std::vector<Pose> poses;
};

class GeoTransform {
public:
    GeoTransform();
    ~GeoTransform();
    
    bool load(const std::string& filename);
    double getResolution() const {
        if(std::abs(_geo_transform[0])<1e-8){
            return std::abs(_geo_transform[1]);
        }; 
        return std::abs(_geo_transform[0]);
    }
    void xy2XY(const double& x, const double& y, double& X, double& Y) const;
    void XY2xy(const double& X, const double& Y, double& x, double& y) const;
private:
    double _geo_transform[6];
    Eigen::Matrix2d _R, _R_inv;
    Eigen::Vector2d _T, _T_inv;
};

class BaseCoveragePlanner{
public:
    BaseCoveragePlanner(const std::string& cfg_file){}
    virtual ~BaseCoveragePlanner(){}
    
    virtual bool planOnPolygon(const std::vector<Point>& outline,
                const std::vector<std::vector<Point> >& exclude_polygons,
                Trajectory& trajectory){return false;};
    virtual bool planOnWholeMap(Trajectory& trajectory){return false;};
    
    void loadMap(const std::string& map_path,
                 const std::string& tfw_path){
        _map = cv::imread(map_path, CV_LOAD_IMAGE_GRAYSCALE);
        _transform.load(tfw_path);
    }
protected:
    cv::Mat _map;
    GeoTransform _transform;
};

}   
}
}


#endif