#ifndef _CAR_H_
#define _CAR_H_

#include <map>
#include <cmath>
#include <vector>


class Car{
public:
    Car(){}
    ~Car(){}
    // set variables
    inline void setWheelbase(const double wheelbase){_wheelbase = wheelbase;}
    inline void setWidth(const double w){_width = w;}
    inline void setLength(const double l){_length = l;}
    inline void setMaxSteer(const double steer){_max_steer = steer;}
    inline void setFootPrintRect(int minx, int maxx, int miny, int maxy){
        _minx = minx;
        _maxx = maxx;
        _miny = miny;
        _maxy = maxy;
    }
    

    // get variables
    inline const double& width()const{return _w;}
    inline const double& length()const{return _l;}
    inline const double& wheelbase()const{return _wheelbase;}
    inline const double minTurningRadius() const{
        return _wheelbase / std::tan(_max_steer);
    }
    inline const double& maxSteer(){return _max_steer;}
    inline const double& minx()const{return _minx;}
    inline const double& maxx()const{return _maxx;}
    inline const double& miny()const{return _miny;}
    inline const double& maxy()const{return _maxy;}
private:
    double _w;
    double _l;
    double _wheelbase;
    double _max_steer;
    double _width;
    double _length;
    double _minx, _miny, _maxx, _maxy;
};

#endif