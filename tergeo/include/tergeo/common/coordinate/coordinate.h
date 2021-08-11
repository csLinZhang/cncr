/**
 * @file coordinate.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 大地坐标转换，投影坐标系：北(X)东(Y)地(Z)
 */
#ifndef _TERGEO_COMMON_COORDINATE_H
#define _TERGEO_COMMON_COORDINATE_H
#include "tergeo/common/macro.h"

namespace tergeo {
namespace common {
namespace coordinate {
/// 投影坐标采用东北天--XYZ
enum EllipsoidType {
    ELPSD_WGS84 = 0,
    ELPSD_CGCS2000 = 1,
    ELPSD_XIAN80 = 2,
    ELPSD_BEIJING54 = 3
};
/// @brief 投影带
enum BandType {
    /// @brief 6度带投影
    BAND6 = 0,
    /// @brief 3度带投影
    BAND3 = 1
};   
/// @brief 
EllipsoidType GetEllipsoid();

/// @brief 设置㮋球参数
void SetEllipsoid(EllipsoidType type);
/**
 * @brief BLH黑心XYZ,地心坐标系
 * @param B 纬度，单位：度
 * @param L 经度，单位：度
 * @param H 大地高，单位：米
 * @param X 经度，单位：米
 * @param Y 经度，单位：米
 * @param Z 经度，单位：米
 */ 
void BLH2XYZ(const double B, const double L, const double H,
             double& X, double& Y, double& Z);
/**
 * @brief BLH黑心XYZ,地心坐标系
 * @param X 经度，单位：米
 * @param Y 经度，单位：米
 * @param Z 经度，单位：米
 * @param B 纬度，单位：度
 * @param L 经度，单位：度
 * @param H 大地高，单位：米
 */
void XYZ2BLH(const double X, const double Y, const double Z,
             double& B, double& L, double& H);

/**
 * @brief 获取中央子午线
 * @param L 输入经度
 * @param band_type 投影带
 */ 
double GetCentralMeridian(const double L, BandType band_type = BAND6);
/**
 * @brief 高斯正投影
 * @param B 纬度 单位：度
 * @param L 经度 单位：度
 * @param X 正东向 6位数+500km 单位：米
 * @param Y 正北向 7位数不带带号 单位：米
 * @param cntL0 中央子午线 单位：度
 */ 
void GaussBL2XY(const double B, const double L, 
    double& X, double& Y, const double cntL0);
/**
 * @brief 高斯反投影
 * @param X 正东向 6位数+500km 单位：米
 * @param Y 正北向 7位数不带带号 单位：米
 * @param B 纬度 单位：度
 * @param L 经度 单位：度
 * @param cntL0 中央子午线 单位：度
 */ 
void GaussXY2BL(const double X, const double Y, 
    double& B, double& L, const double cntL0);
/**
 * @brief UTM正投影
 * @param B 纬度 单位：度
 * @param L 经度 单位：度
 * @param X 正东向 6位数+500km 单位：米
 * @param Y 正北向 7位数不带带号 单位：米
 * @param cntL0 中央子午线 单位：度
 */ 
void UtmBL2XY(const double B, const double L, 
    double& X, double& Y, const double cntL0);
/**
 * @brief 默认：6度带投影
 */
void UtmBL2XY(const double B, const double L, 
    double& X, double& Y);

/**
 * @brief UTM反投影
 * @param X 正东向 6位数+500km 单位：米
 * @param Y 正北向 7位数不带带号 单位：米
 * @param B 纬度 单位：度
 * @param L 经度 单位：度
 * @param cntL0 中央子午线 单位：度
 */ 
void UtmXY2BL(const double X, const double Y, 
    double& B, double& L, const double cntL0);

}
}
}


#endif