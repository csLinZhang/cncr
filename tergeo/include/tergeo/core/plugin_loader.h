#ifndef _TERGEO_CORE_PLUGIN_LOADER_H_
#define _TERGEO_CORE_PLUGIN_LOADER_H_
#include <vector>
#include "tergeo/common/macro.h"
namespace tergeo {
namespace core {
class PluginLoaderPrivate;
class PluginLoader final {
public:
    ~PluginLoader();
    static bool Load(const std::string& plugin_path);
    
    static std::vector<std::string> GetLibPathNameVec();
private:
    PluginLoaderPrivate* _ptr = nullptr;
    DECLARE_SINGLETON(PluginLoader);
};
}
}

#endif