#ifndef _TERGEO_COMMON_VEHICLE_INFO_H
#define _TERGEO_COMMON_VEHICLE_INFO_H

#include <string>
#include <vector>
#include <unordered_map>
#include "tergeo/common/macro.h"
#include "tergeo/common/eigen_utils.h"
#include "tergeo/common/math/point.h"
#include "tergeo/vehicle_info/proto/vehicle_info.pb.h"
namespace tergeo {
namespace vehicle_info {

struct CameraIntrinsic {
    std::string camera_name;
    int width;
    int height;
    double intrinsic[4];
    std::string distortion_model;
    double distortion[8];
};
using CameraTable = 
    std::unordered_map<std::string, std::shared_ptr<CameraIntrinsic> >;

struct UltrasonicIntrinsic {
    std::string ultrasonic_name;
    double horizontal_angle;
    double vertical_angle;
    double min_measurement_dist;
    double max_measurement_dist;
};
using UltrasonicTable =
    std::unordered_map<std::string, std::shared_ptr<UltrasonicIntrinsic> >;

struct SensorExtrinsic {
    std::string sensor_from;
    std::string sensor_to;
    double extrinsic[6]; // ax, ay, az, x, y, z
    
    Eigen::Matrix4d toMatrix() const {
        Eigen::Matrix4d matrix;
        tergeo::common::eigen::ExtrinsicToMatrix(extrinsic, matrix);
        return matrix;
    }
};

class VehicleInfoPrivate;
class IntrinsicPrivate;
class ExtrinsicPrivate;
class VehicleInfo final {
public:
    ~VehicleInfo();
    /**
     * @brief work_path means /tergeo/
     * if work_path.empty() -> work_path = tergeo::core::Application::GetWorkPath(); 
     * vehicle_info.conf -> work_path + "/conf/vehicle_info.conf"
     * calib_dir -> work_path + "/calib_param/" + vehicle_id
     */ 
    static bool Load(const std::string& work_path = "");
    static bool IsInit();

    static std::string GetVehicleID();

    static bool HasCamera(const std::string& camera_name);
    static CameraIntrinsic* GetCamera(const std::string& camera_name);

    static bool HasUltrasonic(const std::string& ultrasonic_name);
    static UltrasonicIntrinsic* GetUltrasonic(const std::string& ultrasonic_name);

    static bool HasExtrinsic(const std::string& sensor_from, 
                             const std::string& sensor_to);
    static SensorExtrinsic* GetExtrinsic(const std::string& sensor_from, 
                                         const std::string& sensor_to);
private:
    VehicleInfoPrivate* _ptr;
    IntrinsicPrivate* _ptr_intrinsic;
    ExtrinsicPrivate* _ptr_extrinsic;
    DECLARE_SINGLETON(VehicleInfo);
};

}
}

#endif