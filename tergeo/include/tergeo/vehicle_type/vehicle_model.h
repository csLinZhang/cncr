#ifndef _TERGEO_VEHICLE_TYPE_VEHICLE_MODEL_H
#define _TERGEO_VEHICLE_TYPE_VEHICLE_MODEL_H
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
namespace tergeo {
namespace vehicle_type {
class VehicleModel : public tergeo::core::IPlugin {
    DECLARE_FACTORY(VehicleModel)
    DECLARE_DEFAULT_STRUCTOR(VehicleModel)
public:
    struct WheelTwist {
        float steer_angle_degree = 0.;
        float front_wheel_speed_mps = 0.;
        float back_left_wheel_speed_mps = 0.;
        float back_right_wheel_speed_mps = 0.;
    };
    struct RealTwist {
        float linear_velocity_mps = 0.;
        float angular_velocity_radps = 0.;
    };

    virtual common::Status init() = 0;
    virtual RealTwist WheelTwistToReal(const WheelTwist& wheel_twist, 
                                       const float wheel_base) const = 0;
    virtual WheelTwist RealTwistToWheel(const RealTwist& real_twist, 
                                        const float wheel_base) const = 0;
};
#define REGISTER_VEHICLE_MODEL_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::vehicle_type::VehicleModel, sub_class);

class TestVehicleModel : public VehicleModel {
    DECLARE_DEFAULT_STRUCTOR(TestVehicleModel)
public:
    virtual common::Status init() override;
    RealTwist WheelTwistToReal(const WheelTwist& wheel_twist, 
                               const float wheel_base) const override;
    WheelTwist RealTwistToWheel(const RealTwist& real_twist, 
                                const float wheel_base) const override;
};
}
}

#endif