/**
 * @file license.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 
 */
#ifndef _TERGEO_CORE_LICENSE_H_
#define _TERGEO_CORE_LICENSE_H_

#include <tergeo/common/macro.h>

namespace tergeo {
namespace core {
class License {
public:
    ~License() = default;

    static bool IsValid();

private:
    DECLARE_SINGLETON(License)
};  
}  // 
}  // 
#endif  // 
