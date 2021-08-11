/**
 * @file byte_utils.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 字节处理，基础函数
 */
#ifndef _TERGEO_COMMON_BYTE_UTIL_H
#define _TERGEO_COMMON_BYTE_UTIL_H

#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace tergeo {
namespace common {
namespace byte {
/// @brief 字节转16进制
std::string ByteToHex(const uint8_t value);

/// @brief 字节转2进制
std::string ByteToBinary(const uint8_t value);
/**
 * @brief 设置指定位为1
 * @param value 输入数据
 * @param pos 从低位算起的二进制位置
 */ 
void SetBitOne(uint8_t& value, const uint8_t pos);
/**
 * @brief 设置指定位为0
 * @param value 输入数据
 * @param pos 从低位算起的二进制位置
 */ 
void SetBitZero(uint8_t& value, const uint8_t pos);
/**
 * @brief 指定位是否为1
 * @param value 输入数据
 * @param pos 从低位算起的二进制位置
 * @return 是否为1
 */ 
bool IsBitOne(const uint8_t value, const uint8_t pos);
/**
 * @brief 指定位是否为0
 * @param value 输入数据
 * @param pos 从低位算起的二进制位置
 * @return 是否为0
 */ 
bool IsBitZero(const uint8_t value, const uint8_t pos);

/**
 * @brief 设置高4位，超出自动截断
 * @param value 给定值
 * @param hight_bits 要修改成的值
 */ 
void SetHighFourBits(uint8_t& value, const uint8_t high_bits);
/**
 * @brief 设置低4位，超出自动截断
 * @param value 给定值
 * @param hight_bits 要修改成的值
 */ 
void SetLowFourBits(uint8_t& value, const uint8_t low_bits);

/// @brief 获取高4位
uint8_t GetHighFourBits(const uint8_t value);
/// @brief 获取低4位
uint8_t GetLowFourBits(const uint8_t value);

/**
 * @brief 设置给定值
 * @param value 输入数据
 * @param sub 要修改成的值
 * @param start_pos 二进制从低位算起的位置
 * @param length 要修改的二进制长度
 */ 
void SetSubByte(uint8_t& value, const uint8_t sub, 
    const uint8_t start_pos, const uint8_t length);
/**
 * @brief 获取指定区间的字符[start_pose, start_pose + length],从低位算起
 */
uint8_t GetSubByte(const uint8_t value, 
    const uint8_t start_pos, const uint8_t length);

}
}
}
#endif