#ifndef _TERGEO_ALGORITHM_ASTAR_H_
#define _TERGEO_ALGORITHM_ASTAR_H_

#include <vector>

namespace tergeo {
namespace planning{
namespace algorithm {
// wrapper of CGAL's function
class Point;
class PolygonPartition{
public:
    static bool partitionPolygon(const std::vector<Point>& in,
                                 std::vector<std::vector<Point>>& out); 
private:
    PolygonPartition();
    ~PolygonPartition();
};
}
}
}
#endif