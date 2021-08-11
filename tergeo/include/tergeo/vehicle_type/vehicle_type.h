#ifndef _TERGEO_COMMON_VEHICLE_TYPE_H
#define _TERGEO_COMMON_VEHICLE_TYPE_H

#include <string>
#include <vector>
#include "tergeo/common/macro.h"
#include "tergeo/common/math/point.h"
#include "tergeo/vehicle_type/vehicle_region.h"
#include "tergeo/vehicle_type/vehicle_model.h"
#include "tergeo/vehicle_type/proto/vehicle_type.pb.h"
namespace tergeo {
namespace vehicle_type {

class VehicleTypePrivate;
class VehicleType final {
public:
    ~VehicleType();
    /**
     * @brief cfg_file.empty() load conf_path + "/vehicle_type.conf" 
     * 
     */ 
    static bool Load(const std::string& cfg_file = "");
    static bool IsInit();

    static std::string GetType();

    static float GetWidth();
    static float GetLength();
    static float GetHeight();
    static float GetWheelBase();
    static float GetMinTurningRadius();
    
    // WheelTwist is the wheels' state from chassis while 
    //     the RealTwist is the particle's state in our tergeo system.
    static VehicleModel::RealTwist WheelTwistToReal(
        const VehicleModel::WheelTwist& wheel_twist);
    static VehicleModel::WheelTwist RealTwistToWheel(
        const VehicleModel::RealTwist& real_twist);
      
    static const common::math::Polyline2f& GetVehicleContour();
    static const common::math::Rect2f& GetContourRect();

    static const VehicleRegion& GetTrumpetRegion();
    static const VehicleRegion& GetEmergencyRegion();
        
    static const VehicleModel* GetVehicleModel();
private:
    VehicleTypePrivate* _ptr;
    DECLARE_SINGLETON(VehicleType);
};

}
}

#endif