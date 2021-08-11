/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                   A MI TUO LE GE FO                  |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                   GOD BLESS NO BUGS!!                 
 *                                                      
 *                        _ooOoo_                   救    
 *                       o8888888o                  赎   
 *                       88" . "88                  之
 *                       (| -_- |)                  道
 *                       0\  =  /0                  就
 *                    ____/'___'\____               在
 *                  .'  \\|     |//  '.             其
 *                 /  \\|||  :  |||//  \            中
 *                /  _||||| -:- |||||_  \
 *                |   | \\\  -  /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  `-`  __/-.  /
 *              ___`..'   /--.--\   `..'___
 *           ."" '<  `.___\_<|>_/___.'  >' "".
 *          | | :  `-\`.;` \ _ / ';.`/- ` : | |
 *          \  \ `-.  \_ __ \ / __ _/  .-` /  /
 *     ======`-.____`-.__\_______/ __.-`___.-'====== 
 *                       `=-----=' 
 *     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef _TERGEO_CORE_FACTORY_H_
#define _TERGEO_CORE_FACTORY_H_
#include <string> 
#include <memory>
#include <dlfcn.h>
#include <unordered_map>

#include "tergeo/common/log.h"
#include "tergeo/common/file/file.h"
#include "tergeo/core/plugin_loader.h"
namespace tergeo {
namespace core {
class IFactory {
public:
    IFactory() = default;
    virtual ~IFactory() = default;
    
    static std::vector<std::string>& GetAdapterFileVec();
    static void AddAdapterFile(const std::string adapter_file);
    
    std::string getConfigPath() const;
    virtual std::string getLibPath() const = 0;
};

template <typename T> 
class BaseFactory : public IFactory {
public:
    BaseFactory() = default;
    virtual ~BaseFactory() = default;
    typedef typename T::Ptr ObjectPtr;
    typedef std::unordered_map<std::string, BaseFactory<T>* > FactoryMap;
    static FactoryMap& GetFactoryMap() {
        static FactoryMap factory_map;
        return factory_map;
    }
    virtual ObjectPtr createInstance() const {return ObjectPtr();}

    static ObjectPtr Create(const std::string& sub_class_name) {
        const FactoryMap& factory_map = GetFactoryMap();
        if (factory_map.find(sub_class_name) == factory_map.end()) {
            return nullptr;
        }
        return factory_map.at(sub_class_name)->createInstance();
    }
    
    static void Register(const std::string& sub_class_name, BaseFactory<T>* factory) {
        FactoryMap& factory_map = GetFactoryMap();
        CHECK(factory_map.find(sub_class_name) == factory_map.end()) 
            << "Conflict register class: " << sub_class_name;
        factory_map[sub_class_name] = factory;
        AddAdapterFile(factory->getConfigPath() + "/" + sub_class_name + ".adapter");
    }
    
    static void Print() {                                                             
        const FactoryMap& factory_map = GetFactoryMap();                                                                                                                  
        AINFO << "=============== begin print ================";                      
        AINFO << "Size: " << factory_map.size();                             
        typename FactoryMap::const_iterator iter;                                              
        for (iter = factory_map.begin(); iter != factory_map.end(); ++iter) {                                                             
            AINFO << iter->first;                         
        }                                                                             
        AINFO << "===============  end print  ================";                      
    }
};
class IPlugin {
public:
    IPlugin() = default;
    virtual ~IPlugin() = default;
    std::string getID() const;
    std::string getClassName() const;
    // return GetConfigPath() + ConfigName
    std::string getConfigFile() const;
    void setConfigFileName(const std::string file);
    std::string getConfigFileName() const;
    
    std::string getMetaData(const std::string key) const;
    bool hasMetaData(const std::string key) const;
    void setMetaData(const std::string key, const std::string value);
    
    std::string getLibPath() const;
    std::string getConfigPath() const;
    
    template <typename ProtoMessageType>                                                  
    bool loadConfigFile(ProtoMessageType& msg) {                                          
        return tergeo::common::file::GetProtoFromFile(getConfigFile(), msg);
    }
public: // for factory
    void setClassName(const std::string class_name);
    void setLibPath(const std::string lib_path);
    void setConfigPath(const std::string config_path);
    void initMetaData();
protected:
    std::unordered_map<std::string, std::string> _metadata;
};

}
}
#define DECLARE_FACTORY(base_class_name)                                                  \
public:                                                                                   \
    typedef tergeo::core::BaseFactory<base_class_name> Factory;                           \
    typedef std::shared_ptr<base_class_name> Ptr;                                                                                 


#define REGISTER_CLASS_CPP(base_class_name, sub_class_name)                               \
    class sub_class_name##Factory : public base_class_name::Factory {                     \
    public:                                                                               \
        explicit sub_class_name##Factory(const std::string& sub_class_name)               \
            : base_class_name::Factory() {Register(sub_class_name, this);}                \
        virtual ~sub_class_name##Factory() = default;                                     \
        virtual base_class_name::Ptr createInstance() const {                             \
            base_class_name::Ptr instance_ptr(new sub_class_name());                      \
            instance_ptr->initMetaData();                                                 \
            instance_ptr->setClassName(#sub_class_name);                                  \
            instance_ptr->setLibPath(getLibPath());                                       \
            instance_ptr->setConfigPath(getConfigPath());                                 \
            return instance_ptr;                                                          \
        }                                                                                 \
        virtual std::string getLibPath() const {                                          \
            Dl_info info;                                                                 \
            if (dladdr((void*)this, &info)) {                                             \
                std::string lib_path(info.dli_fname);                                     \
                std::string::size_type pos = lib_path.find_last_of("/");                  \
                if (pos != std::string::npos) {                                           \
                    return lib_path.substr(0, pos);                                       \
                }                                                                         \
            }                                                                             \
            return std::string();                                                         \
        }                                                                                 \
    };                                                                                    \
    sub_class_name##Factory g_##sub_class_name##_factory(#sub_class_name);

#endif