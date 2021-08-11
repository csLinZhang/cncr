#ifndef _TERGEO_LOCALIZATION_BASE_RELOCALIZER_H_
#define _TERGEO_LOCALIZATION_BASE_RELOCALIZER_H_
#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include "utils.h"
namespace tergeo {
namespace localization {

class BaseRelocalizer : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseRelocalizer)
    DECLARE_DEFAULT_STRUCTOR(BaseRelocalizer)
public:
    virtual common::Status init() = 0;
    virtual common::Status start() {return common::StatusOK();}
    virtual void stop() {}
    
    virtual void relocate(bool use_guess = false, 
        const double x = 0, const double sigma_x = 0, 
        const double y = 0, const double sigma_y = 0,
        const double heading_angle_rad = 0, const double sigma_angle = 0) = 0;
    
    virtual bool getRelocalizationPose(double &x, double &sigma_x,
        double &y, double &sigma_y, double &heading_angle_rad, double &sigma_angle,
        tergeo::localization::TimeStamp &stamp) = 0;
};
#define REGISTER_RELOCALIZER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::localization::BaseRelocalizer, sub_class)
}
} // tergeo 
#endif