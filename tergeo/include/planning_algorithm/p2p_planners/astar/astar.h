#ifndef __TERGEO_PLANNING_PLANNER_PLUGINS_ASTAR_H__
#define __TERGEO_PLANNING_PLANNER_PLUGINS_ASTAR_H__

#include <vector>
#include <map>
#include <stdint.h>
#include "p2p_planners/astar/distance_map.h"

namespace tergeo {
namespace planning {
namespace algorithm{
struct SearchPoint{
public:
    SearchPoint(int row, int col, double c, double h):
        _row(row),_col(col),_cost_so_far(c),_priority(h){}
    int _row;
    int _col;
    double _cost_so_far;
    double _priority;
};

class AStar{
public:
    AStar(){}
    ~AStar();
    bool findPath(const uint8_t* grid_data,
                  const int grid_width,
                  const int grid_height,
                  const int inflation_cell_size,
                  const Cell& start,
                  const Cell& goal,
                  std::vector<Cell>& path);
private:
    void buildGraph(const uint8_t* cdata);
    uint8_t getCost(int distance);
    std::vector<uint8_t> _graph;
    std::vector<bool> _visited;

    DistanceMap _dm;
    
    int _width;
    int _height;
    int _inflation_radius;
    const double _cost_descend_rate = 0.5;
    const uint8_t _grid_lethal_obstacle = 254;
    const uint8_t _grid_inflation_radius = 253;
};
}
}
}

#endif