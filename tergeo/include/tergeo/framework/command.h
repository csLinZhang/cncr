#ifndef _TERGEO_FRAMEWORK_COMMAND_H
#define _TERGEO_FRAMEWORK_COMMAND_H
#include "tergeo/common/macro.h"
namespace tergeo {
namespace framework {
class Command {
public:
    ~Command() = default;

    static bool DoCleanWork(bool enable = true);
    static bool DoCleanWorkButLift(bool enable = true);
    
    static bool OpenLeftTurnLight(bool enable = true);
    static bool OpenRightTurnLight(bool enable = true);
    static bool OpenIndicatorLight(bool enable = true);
    static bool OpenLighting(bool enable = true);
    
    static bool DoEmergencyAlarm(bool enable = true);
    static bool DoEmergencyStop(bool enable = true);
    static bool DoEmergencyStopAndAlarm(bool enable = true);
    static bool DoEmergencyBrake(bool enable = true);
    static bool DoEmergencyBrakeAndAlarm(bool enable = true);
    
    static bool DriveVehicle(bool enable, const float omega_radps,
        const float speed_mps, const bool brake_down = false, 
        const float time_keep_s = 1.0f);

private:
    DECLARE_SINGLETON(Command)
};
}
}

#endif