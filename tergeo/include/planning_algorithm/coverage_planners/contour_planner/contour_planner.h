#ifndef _TERGEO_ALGORITHM_CONTOUR_PLANNER_H_
#define _TERGEO_ALGORITHM_CONTOUR_PLANNER_H_

#include "planning_algorithm/coverage_planners/base_coverage_planner.h"

namespace tergeo {
namespace planning{
namespace algorithm {
/********************************
 *  
 * 
 * 
 * 
*/
class ContourPlanner: public BaseCoveragePlanner{
public:
    template<typename T> struct Point2D{
    public:
        Point2D(T x, T y):_x(x),_y(y){}
        T _x;
        T _y;
    };
    struct Cell{
    public:
        Cell(int r, int c, int d):_row(r),_col(c),_dist_from_obstacle(d){}
        int _row;
        int _col;
        int _dist_from_obstacle;
    };
public:
    ContourPlanner(const std::string& cfg);
    ~ContourPlanner();

    bool planOnPolygon(
            const std::vector<Point>& outline,
            const std::vector<std::vector<Point> >& exclude_polygons,
            Trajectory& trajectory) override;
    virtual bool planOnWholeMap(Trajectory& trajectories);
private:
    void maskMap(const std::vector<Point>& outline,
                 const std::vector<std::vector<Point> >& exclude_polygons);
    bool isPointInPoly(const std::vector<Point>& polygon,
                       double x, double y);
    void appendCells(int r, int c, int distance);
    void computeDistanceMap();

    void getCostmapData(uint8_t* data);
    void debug(const Trajectory& traj);
private:
    void findNearestAndArrangePolygon(const Pose& pose, std::vector<Point>& polygon);
    void coveragePlanForPolygon(const std::vector<Point>& polygon,
                                std::vector<std::vector<Point>>& rounds);
    void removeCollapsedCorners(std::vector<Point>& corners);
    void computeAngles(const std::vector<Point>& corners, 
                       std::vector<double>& angles);
    void computeAngles(const std::vector<Point>& corners, 
                       std::vector<std::pair<double, double>>& neighbor_angles);
    void sampleAlongContour(const std::vector<Point>& corners,
                            Trajectory& traj);
    double getYFromTwoPointsLine(const double x1, const double x2,
                                 const double y1, const double y2,
                                 const double x);
    double getXFromTwoPointsLine(const double x1, const double x2,
                                 const double y1, const double y2,
                                 const double y);
    double getXFromCommoonLine(const double a, const double b,
                               const double c, const double y);
    double getYFromCommoonLine(const double a, const double b,
                               const double c, const double x);
    bool getCrossCoordinate(const double a1, const double b1,const double c1,
                            const double a2, const double b2,const double c2,
                            double& x, double& y);
    void getCommonLinePara(const double x1, const double x2,
                           const double y1, const double y2,
                           double &a,double &b,double &c);
    
    // scale down polygon to avoid border collision when robot running.
    // if the scaled polygon is illegal,return false.
    bool zoomInPolygon(const std::vector<Point>& poly,
                       const double offset,
                       std::vector<Point>& out);
private:
    double _contour_distance = 0.6;
    double _inflation_radius = 1.0;

    int _width;
    int _height;
    float _resolution;
    std::vector<bool> _visited;
    std::map<int, std::vector<Cell> > _distance_map;
};
}
}
}//tergeo
 
#endif