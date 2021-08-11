#ifndef _TERGEO_PREDICTION_OBSTACLE_QUEUE_H
#define _TERGEO_PREDICTION_OBSTACLE_QUEUE_H
#include "tergeo/common/common.hpp"

namespace tergeo {
namespace prediction {

struct Obstacle {
    double stamp;

    ObstacleType type;

    common::math::Point3d position;
    common::math::Point3dList points;
};

using ObstacleList = std::list<Obstacle>;

enum ObstacleState {
    OBSTACLE_STATE_UNKNOWN = 0,
    OBSTACLE_STATE_TRACKING = 1,
    OBSTACLE_STATE_LOSE = 2,
    OBSTACLE_STATE_OUTROI = 3
};

struct ObstacleInfo {
    ObstacleInfo() : intent(OBSTACLE_INTENT_UNKNOWN), 
        speed_mps(0), period(0) {}

    ObstacleIntent intent;
    common::math::Pose2d current_pose;
    common::math::Box3d box;

    float speed_mps;
    
    ObstacleType type;

    float period;
    common::math::Pose2dList trajectory;
};

class ObstacleQueue {
public:
    using iterator = ObstacleList::iterator;
    using const_iterator = ObstacleList::const_iterator;
    DECLARE_SHARED_PTR(ObstacleQueue)
    ObstacleQueue();
    virtual ~ObstacleQueue() = default;
    
    std::string getID() const {return _id;}

    void enqueue(const Obstacle& obstacle);
    
    ObstacleList* getObstacleList() {return &_obstacle_list;}
    const ObstacleList* getObstacleList() const {return &_obstacle_list;}
    
    Obstacle* getLastestObstacle() {return &(_obstacle_list.back());}
    const Obstacle* getLastestObstacle() const {return &(_obstacle_list.back());}

    Obstacle* getOldestObstacle() {return &(_obstacle_list.front());}
    const Obstacle* getOldestObstacle() const {return &(_obstacle_list.front());}

    iterator begin() {return _obstacle_list.begin();}
    iterator end() {return _obstacle_list.end();}

    bool empty() {return _obstacle_list.empty();}

    void setState(ObstacleState state) {_state = state;}
    ObstacleState getState() const {return _state;}
    
    ObstacleInfo* getObstacleInfo() {return &_obstacle_info;}
    const ObstacleInfo* getObstacleInfo() const {return &_obstacle_info;}

    void checkSize(const int max_size);
private:
    std::string _id;
    ObstacleList _obstacle_list;
    ObstacleState _state = OBSTACLE_STATE_UNKNOWN;

    ObstacleInfo _obstacle_info;
    
    DISALLOW_COPY_AND_ASSIGN(ObstacleQueue)
};

}
}

#endif