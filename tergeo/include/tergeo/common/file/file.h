/**
 * @file file.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 文件存储取读取
 */
#ifndef _TERGEO_COMMON_FILE_H_
#define _TERGEO_COMMON_FILE_H_

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"

#include "tergeo/common/log.h"
#include "tergeo/common/string/string.h"
#include "tergeo/common/file/file_system.h"
namespace tergeo {
namespace common {
namespace file {
/**
 * @brief 将proto内容以ASCII写入文件
 * @param message proto数据
 * @param file_descriptor 文件ID
 * @return 返回是否写成功
 */
template <typename MessageType>
bool SetProtoToASCIIFile(const MessageType &message, int file_descriptor) {
    using google::protobuf::TextFormat;
    using google::protobuf::io::FileOutputStream;
    using google::protobuf::io::ZeroCopyOutputStream;
    if (file_descriptor < 0) {
        AERROR << "Invalid file descriptor.";
        return false;
    }
    ZeroCopyOutputStream *output = new FileOutputStream(file_descriptor);
    bool success = TextFormat::Print(message, output);
    delete output;
    close(file_descriptor);
    return success;
}

/**
 * @brief 将proto内容以ASCII写入文件
 * @param message proto数据
 * @param file_name 文件名
 * @return 返回是否写成功
 */
template <typename MessageType>
bool SetProtoToASCIIFile(const MessageType &message,
                         const std::string &file_name) {
    int fd = open(file_name.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd < 0) {
        AERROR << "Unable to open file " << file_name << " to write.";
        return false;
    }
    return SetProtoToASCIIFile(message, fd);
}

/**
 * @brief 以ASCII形式读文件
 * @param file_name 文件名
 * @param message proto数据
 * @return 返回是读成功
 */
template <typename MessageType>
bool GetProtoFromASCIIFile(const std::string &file_name, MessageType& message) {
    using google::protobuf::TextFormat;
    using google::protobuf::io::FileInputStream;
    using google::protobuf::io::ZeroCopyInputStream;
    int file_descriptor = open(file_name.c_str(), O_RDONLY);
    if (file_descriptor < 0) {
        AERROR << "Failed to open file " << file_name << " in text mode.";
        return false;
    }
  
    ZeroCopyInputStream *input = new FileInputStream(file_descriptor);
    bool success = TextFormat::Parse(input, &message);
    if (!success) {
        AERROR << "Failed to parse file " << file_name << " as text proto.";
    }
    delete input;
    close(file_descriptor);
    return success;
}

/**
 * @brief 将proto内容以二进制形式写入文件
 * @param message proto数据
 * @param file_name 文件名
 * @return 返回是否写成功
 */
template <typename MessageType>
bool SetProtoToBinaryFile(const MessageType &message,
                          const std::string &file_name) {
    std::fstream output(file_name,
                        std::ios::out | std::ios::trunc | std::ios::binary);
    return message.SerializeToOstream(&output);
}

/**
 * @brief 以二进制形式读文件
 * @param file_name 文件名
 * @param message proto数据
 * @return 返回是读成功
 */
template <typename MessageType>
bool GetProtoFromBinaryFile(const std::string &file_name,
                            MessageType& message) {
    std::fstream input(file_name, std::ios::in | std::ios::binary);
    if (!input.good()) {
        AERROR << "Failed to open file " << file_name << " in binary mode.";
        return false;
    }
    if (!message.ParseFromIstream(&input)) {
        AERROR << "Failed to parse file " << file_name << " as binary proto.";
        return false;
    }
    return true;
}

/**
 * @brief 读proto文件
 * @param file_name 文件名
 * @param message proto数据
 * @return 返回是读成功
 */
template <typename MessageType>
bool GetProtoFromFile(const std::string &file_name, MessageType& message) {
    // Try the binary parser first if it's much likely a binary proto.
    if (file_name.empty()) {
        AERROR << "Empty file name!!";
        return false;
    }
    if (!tergeo::common::file_system::Exists(file_name)) {
        AERROR << "Not exist file: " << file_name;
        return false;
    }
    if (string::EndWith(file_name, ".bin")) {
      return GetProtoFromBinaryFile(file_name, message) ||
             GetProtoFromASCIIFile(file_name, message);
    }
    return GetProtoFromASCIIFile(file_name, message) ||
           GetProtoFromBinaryFile(file_name, message);
}

/**
 * @brief 读文本
 * @param file_name 文件名
 * @param content 文本内容
 * @return 返回是读成功
 */
bool GetContent(const std::string &file_name, std::string& content);

}  // namespace file
}  // namespace common
}  // namespace tergeo

#endif  // _TERGEO_COMMON_FILE_H_
