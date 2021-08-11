#ifndef _TERGEO_PLANNING_FRAME_H
#define _TERGEO_PLANNING_FRAME_H
#include "tergeo/common/common.hpp"
#include "tergeo/planning/utils.h"
#include "tergeo/map/area.h"
#include "tergeo/map/raster.h"
#include "tergeo/map/reference_line.h"
#include "tergeo/pipeline/proto/task.pb.h"

namespace tergeo {
namespace planning {
using Task = tergeo::pipeline::proto::Task;

class FramePrivate;
class Frame {
public:
    Frame();
    ~Frame();

    bool init();
    
    bool schedule();
    bool observe();

    const common::math::Pose2d& getCurrentPose() const;
    const VehicleState& getVehicleState() const; 
    
    const ObstacleList& getObstacles() const;
    
    bool startTask() const;
    bool finishTask() const;
    const Task& getTask() const;

    const tergeo::map::Area* getArea() const;
    const tergeo::map::Raster* getRaster() const;
    const tergeo::map::ReferenceLine* getReferenceLine() const;
private:
    FramePrivate* _ptr = nullptr;    
};

}
}

#endif