#ifndef _GRID_MAP_H_
#define _GRID_MAP_H_

#include <string>
#include "car.h"
#include "pose_2d.h"
#include "node.h"

/*******************************************
 * the map's coodinate is Cartesian coodinate system.
*/
class GridMap{
public:
    GridMap() = delete;
    GridMap(int w, int h, double resolution, uint8_t default_value);
    ~GridMap(){};
    void setOrigin(const double ox, const double oy);
    bool fillData(const uint8_t* input, int w, int h);

    int getWidth() const {return _width;}
    int getHeight() const {return _height;}
    double getResolution() const {return _resolution;}
    bool isCollision(const Car& car, const Pose2D& pose);
    const uint8_t* getData(){return _data.data();}
    void rc2xy(const int r, const int c, double& x, double& y);
    void xy2rc(const double x, const double y, int &r, int& c);
private:
    int _width;
    int _height;
    double _resolution;
    double _origin_x = 0;
    double _origin_y = 0;
    std::vector<uint8_t> _data;

    const int _obstacle_thresh = 50;

};

#endif