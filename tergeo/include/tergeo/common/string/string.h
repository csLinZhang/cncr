/**
 * @file string_utils.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 字符串处理函数
 */
#ifndef _TERGEO_COMMON_STRING_UTIL_H_
#define _TERGEO_COMMON_STRING_UTIL_H_

#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace tergeo {
namespace common {
namespace string {

/**
 * @brief 检查字符串是否以某一标识结尾.
 * @param ori 输入待检核字符串
 * @param pattern 标识
 * @return 是否以标识结尾
 */
inline bool EndWith(const std::string& ori, const std::string& pattern) {
    size_t pos = ori.length() - pattern.length();
    return pos < 0 ? false : ori.substr(pos, pattern.length()) == pattern;
}
/**
 * @brief 检查字符串是否以某一标识开始.
 * @param ori 输入待检核字符串
 * @param pattern 标识
 * @return 是否以标识开始
 */
inline bool StartWith(const std::string& ori, const std::string& pattern) {
    return ori.length() - pattern.length() < 0 ? false : ori.substr(0, pattern.length()) == pattern;
}

/**
 * @brief 分割字符串
 * @param [in]: 输入待分割的字符串
 * @param [in]: 分割字符
 * @param [out]: 分割后的字符列表
 **/
void Split(const std::string& str, char ch, std::vector<std::string>& result);

/**
 * @brief: 去除字符串左侧空格
 * @param [in/out]: 输入/输出字符串
 **/
void TrimLeft(std::string& str);

/**
 * @brief: 去除字符串右侧空格
 * @param [in/out]: 输入/输出字符串
 **/
void TrimRight(std::string& str);

/**
 * @brief: 去除字符串左侧与右侧空格
 * @param [in/out]: 输入/输出字符串
 **/
void TrimBoth(std::string& str);
/**
 * @brief: 将字符串转全大写
 * @param [in]: 输入/输出字符串
 * @return : 输出全大写字符串
 **/
std::string Upper(const std::string& str);
/**
 * @brief: 将字符串转全小写
 * @param [in]: 输入/输出字符串
 * @return : 输出全小写字符串
 **/
std::string Lower(const std::string& str);

std::string Replace(const std::string& str, const std::string src, const std::string dst);

}  // 
}  // 
}  // 
#endif  // 
