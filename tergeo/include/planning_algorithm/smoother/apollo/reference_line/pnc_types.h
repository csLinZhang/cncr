#pragma once
#include <string>

namespace tergeo{
namespace common{
class  PathPoint{
public:
    PathPoint(){}
    ~PathPoint(){}
    const double x() const {return _x;}
    const double y() const{return _y;}
    const double z() const{return _z;}
    const double theta() const{return _theta;}
    const double s() const{return _s;}

    void set_x(double x){ _x = x;}
    void set_y(double y){ _y = y;}
    void set_z(double z){ _z = z;}
    void set_theta(double theta){ _theta = theta;}
    void set_s(double s){ _s = s;}
private:
    double _x;
    double _y;
    double _z;

    // direction on the x-y plane
    double _theta;
    // accumulated distance from beginning of the path
    double _s;

    // curvature on the x-y planning
    double kappa;
    // derivative of kappa w.r.t s.
    double dkappa;
    // derivative of derivative of kappa w.r.t s.
    double ddkappa;
    // The lane ID where the path point is on
    std::string lane_id;

    // derivative of x and y w.r.t parametric parameter t in CosThetareferenceline
    double x_derivative;
    double y_derivative;
};
class SLPoint{
public:
    const double s() const{return _s;}
    const double l() const{return _l;}
    void set_s(double s){ _s = s;};
    void set_l(double l){ _l = l;};
    double _s;
    double _l;
};
}
}
