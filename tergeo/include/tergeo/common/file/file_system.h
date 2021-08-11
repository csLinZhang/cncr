/**
 * @file file_system.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 文件系统基础操作
 */
#ifndef _TERGEO_COMMON_FILE_SYSTEM_H
#define _TERGEO_COMMON_FILE_SYSTEM_H

#include <string>
#include <vector>

namespace tergeo {
namespace common {
namespace file_system {

/// @brief 判断文件或文件夹是否存在
bool Exists(const std::string& file);
/// @brief 判断是否为文件夹
bool IsFolder(const std::string& file);
// @brief 判断是否为文件
bool IsRegularFile(const std::string& file);

/// @brief 在root目录下创建folder文件夹
std::string Mkdir(std::string root, std::string folder);

/**
 * @brief 创建文件夹path
 * @param path 输入路径，绝对或相对路径
 * @param remove_if_exist 如果存在是否删除，如果选ture，则将删除后重建，否则不删除
 */ 
bool Mkdir(std::string path, bool remove_if_exist = false);
/// @brief 重新命名文件或文件夹 from_path -> to_path; 若from_path 不存在返回false
bool Rename(std::string from_path, std::string to_path);
/// @brief 拷贝文件或文件夹 from_path -> to_path; 若from_path 不存在返回false
bool Copy(std::string from_path, std::string to_path);
/// @brief 删除文件或文件夹
bool Remove(std::string path);
/** 
 * @brief 获取文件的后辍名
 * @param filename 文件名：/home/data/filename.txt
 * @return 返回 txt
 */ 
std::string GetSuffix(const std::string& filename);
/** 
 * @brief 获取文件所在目录名
 * @param filename 文件名：/home/data/filename.txt
 * @return 返回 /home/data/
 */
std::string GetFilePath(const std::string& filename); // return /home/data
/** 
 * @brief 获取文件名
 * @param filename 文件名：/home/data/filename.txt
 *     如果是路径名：/home/data/file 则返回: file
 * @return 返回 filename
 */
std::string GetFileName(const std::string& filename); // return filename
/** 
 * @brief 获取带后辍的路径名名文件名
 * @param filename 文件名：/home/data/filename.txt
 * @return 返回 filename.txt
 */
std::string GetAbsFileName(const std::string& filename); // return filename.txt

/** 
 * @brief 获取x给定路径下所有的文件夹全路径名
 * @param in 给定路径
 * @param out 子文件夹全路径列表 
 * @return 子文件夹个数
 */
int GetSubFolders(const std::string& path, std::vector<std::string>& folder_vec);

/**
 * @brief 获取x给定路径下的所有后缀名为sub_str的文件
 * @param in 给定路径 指定后缀名
 * @param out 所有后缀名为sub_str的文件
 * @return 符合条件的文件个数
 */
int GetFiles(const std::string& path, std::vector<std::string>& file_path_vec, std::string sub_str = "", bool sort_up = true);

}
}
}
#endif
