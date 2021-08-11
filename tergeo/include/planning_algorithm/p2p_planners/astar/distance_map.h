#ifndef __TERGEO_PLANNING_PLANNER_PLUGINS_DISTANCE_MAP_H__
#define __TERGEO_PLANNING_PLANNER_PLUGINS_DISTANCE_MAP_H__

#include <vector>
#include <map>
#include <stdint.h>
namespace tergeo {
namespace planning {
namespace algorithm{
struct Cell{
public:
    Cell(int r,int c):_row(r),_col(c){}
    int _row;
    int _col;
};

struct CellWithDist: public Cell{
public:
    CellWithDist(int r, int c, int d): Cell(r, c),_dist_from_obstacle(d){}
    int _dist_from_obstacle;
};



class DistanceMap{
public:
    DistanceMap(){}
    ~DistanceMap();
   
    void buildDistanceMap(const uint8_t* cdata, int w, int h, int obstacle_thresh);
    const std::map<int, std::vector<CellWithDist>>& getDistanceMap(){
        return _cells_cache;
    }
private:
    void appendCells(int r, int c, int distance);
    std::vector<bool> _visited;
    std::map<int, std::vector<CellWithDist> > _cells_cache;
    
    int _width;
    int _height;
};
}
}
}

#endif