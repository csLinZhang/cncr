#ifndef _TERGEO_ALGORITHM_BOW_SHAPE_PLANNER_H_
#define _TERGEO_ALGORITHM_BOW_SHAPE_PLANNER_H_

#include "planning_algorithm/coverage_planners/base_coverage_planner.h"

namespace tergeo{
namespace planning{
namespace algorithm{
// TODO(wz): make the switch order of polygon efficient
class BowShapePlanner:public BaseCoveragePlanner{
public:
    BowShapePlanner(const std::string& cfg_file);
    ~BowShapePlanner(){}
    // the param 'exclude_polygons' has not been taken into acount
    // the input polygon must in order(clockwise or counter-clockwise)
    virtual bool planOnPolygon(
            const std::vector<Point>& polygon,
            const std::vector<std::vector<Point> >& exclude_polygons,
            Trajectory& trajectories);
    // not implemented in this class
    virtual bool planOnWholeMap(Trajectory& trajectories);
private:
    void getCostmapData(uint8_t* data);
    // scale down polygon to avoid border collision when robot running.
    // if the scaled polygon is illegal,return false.
    bool zoomInPolygon(const std::vector<Point>& poly, std::vector<Point>& out);
    void findLongestEdgeIndex(const std::vector<Point>& polygon, int* idx);
    // find line segment's y coordinate at given x
    bool findIntersection(
            const double x, const Point& seg_a, const Point& seg_b, Point* pt);
    void getBoundary(const std::vector<Point>& poly, double* minx,
               double* miny, double* maxx, double* maxy);
    // rotate polygon of rad along origin
    void rotate(const std::vector<Point>& int_poly,
                const double rad,
                std::vector<Point>* out_poly);
    // rotate pt of rad along origin
    void rotate(const Point& in_pt, const double rad, Point* out_pt);
    // interpolate points between a and b, using the map's resolution
    void interpolate(const Point&a, const Point&b, std::vector<Point>* pts);
private:
    double _border_offset = 0.6;
    double _line_space = 0.6;
};

}
}
}
#endif