#ifndef _TERGEO_PLANNING_COSTMAP2D_H_
#define _TERGEO_PLANNING_COSTMAP2D_H_
#include "tergeo/common/common.hpp"

namespace tergeo {
namespace planning {
//
//  (ox, oy) -------->x
//   |               |  
//   |               |   
//   |               |  
//   |               |  
//  \|/--------------
//   y
//   
//   X = ox + x * res
//   Y = oy + y * res
static const uint8_t COST_NO_INFORMATION = 255;
static const uint8_t COST_LETHAL_OBSTACLE = 254;
static const uint8_t COST_INSCRIBED_INFLATED_OBSTACLE = 253;
static const uint8_t COST_FREE_SPACE = 0;

class Costmap2D {
public:
    Costmap2D();
    Costmap2D(const Costmap2D& map);
    Costmap2D(const int width, const int height, const double resolution, 
        const uint8_t default_value = COST_NO_INFORMATION);
    virtual ~Costmap2D();
    
    bool init(const int width, const int height, const double resolution, 
        const uint8_t default_value = COST_NO_INFORMATION);
    Costmap2D& operator=(const Costmap2D& other);

    void reset();
    void reset(const int width, const int height);
    
    double getResolution() const {return _grid.getResolution();}
    int getWidth() const {return _grid.getWidth();}
    int getHeight() const {return _grid.getHeight();}
    double getOriginX() const {return _grid.getOriginX();}
    double getOriginY() const {return _grid.getOriginY();} 
    
    void setDefaultValue(const uint8_t value) {_grid.setDefaultValue(value);}
    uint8_t getDefaultValue() const {return _grid.getDefaultValue();}

    uint8_t* getData() {return _grid.getData();}
    const uint8_t* getData() const {return _grid.getData();}

    bool isValid() const {return _is_init.load();}

    // return mx in [0, width), my in [0, height)
    bool mapToWorld(const int mx, const int my, double& wx, double& wy) const;
    bool worldToMap(const double wx, const double wy, int& mx, int& my) const;
    bool isInCostmap(const double wx, const double wy) const;

    void updateOrigin(const double wx, const double wy);
    void updateCenter(const double wx, const double wy);
    
    void fill(const double X, const double Y, const uint8_t value);
    void fillPolygon(const common::math::Polyline2d& polygon, const uint8_t value);
    common::math::Grid2<double, uint8_t>* getGrid() {return &_grid;}

    bool checkPose(const tergeo::common::math::Pose2d& pose,
                   const tergeo::common::math::Rect2f& foot_rect,
                   const float padding = 0.1) const;
    bool checkPose(const tergeo::common::math::Pose2d& pose,
                   const std::vector<tergeo::common::math::Polyline2f>& include_region,
                   const std::vector<tergeo::common::math::Polyline2f>& exclude_region) const;
private:
    std::atomic<bool> _is_init{false};
    mutable std::mutex _mutex;

    common::math::Grid2<double, uint8_t> _grid;
};

}
}

#endif