/**
 * @file application.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 应用程序，在初化时调用
 * @details 对于程序：path: /home/ppgui/tongji/install/app/tergeo
 *     GetAppName（）返回： tergeo
 *     GetAppPath（）返回： /home/ppgui/tongji/install/app
 *     GetAppPathName() 返回： /home/ppgui/tongji/install/app/tergeo
 *     GetCurrentPath() 返回当前终端所在目录
 *     GetWorkPath() 返回上二级目录：/home/ppgui/tongji/install
 */ 
#ifndef _TERGEO_CORE_APPLICATION_H
#define _TERGEO_CORE_APPLICATION_H
#include "tergeo/common/macro.h"
#include "tergeo/common/log.h"

namespace tergeo {
namespace core {
class ApplicationPrivate;
/// @brief 静态类，全局可用
class Application final {
public:
    ~Application();
    /// @brief 通过命令行初始化
    static void Init(int argc, char** argv);
    /// @brief 返回是否已经初始化
    static bool IsInit();
    /// @brief 返回当前程序名
    static std::string GetAppName();
    /// @brief 返回程序所在目录
    static std::string GetAppPath();
    /// @brief 返回程序全路径名
    static std::string GetAppPathName();
    /// @brief 返回当前终端所在路径
    static std::string GetCurrentPath();
    /// @brief 返回应用程序所在目录的上一级目录: /tergeo/
    static std::string GetWorkPath(); 
    /// @brief 返回conf文件夹路径： GetWorkPath() + "/conf"
    static std::string GetConfPath();
    /**
     * @brief 保证输入路径为绝对路径
     * @param path 输入路径，若path为空或path不存在时，直接返回;
     *     再根据path第一个字符是否为‘/’判断是否为绝对路径，
     *     或是直接返回，若不是返回GetWorkPath() + path;
     * @return 返回绝对路径
     */ 
    static std::string GetAbsolutePath(std::string path);
    
    /// return GetWorkPath() + "/log";
    static std::string GetLogPath();
    /// return GetWorkPath() + "/storage";
    static std::string GetStoragePath();
    /// return GetWorkPath() + "/calib_data";
    static std::string GetCalibPath();
    /// return GetWorkPath() + "/map_data";
    static std::string GetMapPath();
    /// return GetMapPath() + "/areas";
    static std::string GetMapAreasPath();
    /// return GetMapPath() + "/ref_lines";
    static std::string GetRefLinesPath();
    /// return GetMapPath() + "/pipeline";
    static std::string GetPipelinesPath();
private:
    ApplicationPrivate* _ptr;
    DECLARE_SINGLETON(Application);
};
}
}

#endif