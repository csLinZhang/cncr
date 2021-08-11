/**
 * @file status.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 状态
 */
#ifndef _TERGEO_COMMON_STATUS_H_
#define _TERGEO_COMMON_STATUS_H_

#include <string>
#include <tergeo/common/utils.h>
#include <tergeo/common/log.h>
namespace tergeo {
namespace common {

class Status final {
public:
    Status();
    explicit Status(const int code);
    Status(const Status& status);
    Status(const int code, const std::string msg);
    ~Status() = default;
  
    bool isOK() const;
    bool isError() const;
    int getErrorCode() const;

    Status& operator=(const Status& status);
    bool operator==(const Status &rh) const;
    bool operator!=(const Status &rh) const;
  
    std::string getErrorMessage() const {return _msg;}
  
    std::string toString() const;

    void printInfo() {
        if (isOK()) {return;}
        AINFO << getErrorCode() << ", " << _msg;
    }
    void printWarn() {
        if (isOK()) {return;}
        AWARN << getErrorCode() << ", " << _msg;
    }
    void printError() {
        if (isOK()) {return;}
        AERROR << getErrorCode() << ", " << _msg;
    }

    static void SetModuleType(const int type);

private:
    int _code;
    std::string _msg;
};

inline std::ostream &operator<<(std::ostream &os, const Status &s) {
    os << s.toString();
    return os;
}

inline Status StatusOK() {
    return Status(ERROR_OK);
}

inline Status StatusError(const int code, const std::string str) {
    return Status(code, str);
}
inline Status StatusError(const int code, const std::string str, 
        const std::string sub) {
    char buf[256] = {0};
    snprintf(buf, sizeof(buf), str.c_str(), sub.c_str());
    return Status(code, std::move(std::string(buf)));
}

template<typename... Args>
inline Status StatusError(const int code, const std::string str, Args&&... args) {
    char buf[256] = {0};
    snprintf(buf, sizeof(buf), str.c_str(), std::forward<Args>(args)...);
    return Status(code, std::move(std::string(buf)));
}

}  // namespace 
}  // namespace 
#endif  // 
