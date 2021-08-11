#ifndef _TERGEO_PREDICTION_OBSTACLE_CONTAINER_H
#define _TERGEO_PREDICTION_OBSTACLE_CONTAINER_H
#include "tergeo/prediction/obstacle_queue.h"

namespace tergeo {
namespace prediction {

class ObstacleContainer {
public:
    ObstacleContainer() = default;
    virtual ~ObstacleContainer() = default;
    
    void clean();
    void check(const int max_queue_size);

    ObstacleQueue* addObstacleQueue();
    ObstacleQueue* findNearestObstacleQueue(
        const common::math::Point3d& point, float& distance);
        
    int findRadiusObstacleQueue(const common::math::Point3d& point, const float radius, 
        std::vector<ObstacleQueue*>& obstalce_queue_vec, std::vector<float>& dist_vec);

    std::map<std::string, ObstacleQueue::Ptr>* getObstacleMap() {return &_obstacle_map;}
    const std::map<std::string, ObstacleQueue::Ptr>* getObstacleMap() const {return &_obstacle_map;}
private:
    std::map<std::string, ObstacleQueue::Ptr> _obstacle_map;
};

}
}

#endif