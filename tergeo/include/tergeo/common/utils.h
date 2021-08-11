/**
 * @file utils.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 基础结构体定义
 */
#ifndef _TERGEO_COMMON_UTILS_H_
#define _TERGEO_COMMON_UTILS_H_
#include <chrono>
#include <ctime>

namespace tergeo {

class NullType {};

enum Switch {
    TURN_OFF = 0,
    TURN_ON =1
};

enum MessageLevel {
    MESSAGE_INFO = 0,
    MESSAGE_WARNING = 1,
    MESSAGE_ERROR = 2,
    MESSAGE_FATAL = 3
};
/// 
///   \ 4 |     | 2 /
///    \  |  1  |  /
///  16 \ |     | /  8
///      \|     |/
/// --------------------
///    64 |body |    32
/// --------------------
///         128

enum VehicleRegionFlag {
    VEHICLE_REGION_NULL = 0,
    VEHICLE_REGION_FRONT = 1,
    VEHICLE_REGION_FRONT_RIGHT = 2,
    VEHICLE_REGION_FRONT_LEFT = 4,
    VEHICLE_REGION_RIGHT_FRONT = 8,
    VEHICLE_REGION_LEFT_FRONT = 16,
    VEHICLE_REGION_RIGHT = 32,
    VEHICLE_REGION_LEFT = 64,
    VEHICLE_REGION_BACK = 128
};

enum ObstacleType {
    OBSTACLE_TYPE_UNKNOWN = 0,
    OBSTACLE_TYPE_MOVABLE = 1,
    OBSTACLE_TYPE_UNMOVABLE = 2,
    OBSTACLE_TYPE_PEDESTRIAN = 3,
    OBSTACLE_TYPE_BICYCLE = 4,
    OBSTACLE_TYPE_VEHICLE = 5,
    OBSTACLE_TYPE_MAX_TYPE = 6,
};

enum ObstacleIntent {
    OBSTACLE_INTENT_UNKNOWN = 0,
    OBSTACLE_INTENT_STATIONARY = 1,
    OBSTACLE_INTENT_STOP = 2,
    OBSTACLE_INTENT_MOVING = 3,
    OBSTACLE_INTENT_CHANGE_LANE = 4,
    OBSTACLE_INTENT_UTURN = 5,
    OBSTACLE_INTENT_TURN_LEFT = 6,
    OBSTACLE_INTENT_TURN_RIGHT = 7,
    OBSTACLE_INTENT_WALK_AROUND = 8,
    
    OBSTACLE_INTENT_LOW_ACCELERATION = 9,
    OBSTACLE_INTENT_HIGH_ACCELERATION = 10,
    OBSTACLE_INTENT_LOW_DECELERATION = 11,
    OBSTACLE_INTENT_HIGH_DECELERATION = 12
};

enum ModuleType {
    MODULE_UNKNOWN = 0,
    MODULE_LOCALIZATION = 1,
    MODULE_PERCEPTION = 2,
    MODULE_PREDICTION = 3,
    MODULE_PLANNING = 4,
    MODULE_CONTROL = 5,
    MODULE_VEHICLE = 6,
    MODULE_GUARDIAN = 7,

    MODULE_MONITOR = 8,
    MODULE_GUI = 9,
    MODULE_SERVICE = 10,
    MODULE_DRIVER = 11,
    MODULE_MAPPING = 12,

    MODULE_SENSOR = 20,

    MODULE_USER_DEFINE = 50
};

enum NotifyFlag {
    NOTIFY_NULL = 0,
    NOTIFY_INFO = 1,
    NOTIFY_WARN = 2,
    NOTIFY_ERROR = 3,

    NOTIFY_STATUS_ERROR = 10
};

enum ErrorCode {
    ERROR_OK = 0,
    ERROR_UNKNOWN = 1,

    ERROR_INIT = 2,   
    ERROR_START = 3,  
    ERROR_CHECK = 4, 

    ERROR_CONFIG_LOAD = 5,
    ERROR_INSTANCE_CREATE = 6,

};

enum CleanWorkFlag {
    CLEAN_NULL = 0,
    CLEAN_SWEEP = 1,
    CLEAN_LIFT = 2,
    CLEAN_WATER = 4,
    CLEAN_DO_ALL = CLEAN_SWEEP | CLEAN_LIFT | CLEAN_WATER
};
enum LightFlag {
    LIGHT_NULL = 0,
    LIGHT_TURN_LEFT = 1,
    LIGHT_TURN_RIGHT = 2,
    LIGHT_INDICATOR_LIGHT = 4,
    LIGHT_LIGHTING = 8
};
enum EmergencyLevel {
    EMERGENCY_NULL = 0,
    EMERGENCY_ALARM = 1,
    EMERGENCY_STOP = 2,
    EMERGENCY_STOP_ALARM = 4,
    EMERGENCY_BRAKE = 8,
    EMERGENCY_BRAKE_ALARM = 16    
};
}

#endif