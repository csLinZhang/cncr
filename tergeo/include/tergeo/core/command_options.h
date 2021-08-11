/**
 * @file command_options.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 命令行参数解析类
 * @details 使用示例
 *     int main(int argc, char** argv) {
 *         std::string file = "";
 *         TergeoCmdOpts::AddOption("file,f", file, "input file name");
 *         TergeoCmdOpts::Parse(argc, argv);
 *         if (file.empty()) {
 *             std::cout << "empty file" << std::endl;
 *             TergeoCmdOpts::PrintHelp();
 *             return 1;
 *         }
 *         return 0;
 *     }
 *     
 *     可以使用
 *     exec --file filename 或者 exec -f filename
 *     使用 exec --help 可查看帮助
 */

#ifndef _TERGEO_CORE_COMMAND_OPTIONS_H_
#define _TERGEO_CORE_COMMAND_OPTIONS_H_
#include <string>
#include <vector>
#include <iostream>
#include "tergeo/common/macro.h"
#include <boost/program_options.hpp>

namespace tergeo {
namespace core {
/// @brief 单例静态类，命令行解析类
class CommandOptions final {
public:
    ~CommandOptions() = default;
    
	/**
	 * @brief 添加命令选项
	 * @param option 命令名，支持简写，如"file" --file;(file,f) 可用--file或者-f
	 * @param value 输入值
	 * @param describe 描述，--help时提示
	 */ 
    template <class T> 
	static void AddOption(std::string option, T& value, std::string describe) {
		Instance()->_options.add_options()(option.c_str(), boost::program_options::value<T>(&value), describe.c_str());
	}
    
	/**
	 * @brief 添加一对多命令
	 * @param option 命令名，支持简写，如"file" --file;(file,f) 可用--file或者-f
	 * @value 输入std::vector<T>类型，将会解析多个
	 * @describe 描述，--help时提示
	 */ 
    template <class T> // support: -f 1.jpg 2.jpg 3.jpg; while addOption: -f 1.jpg -f 2.jpg -f 3.jpg 
	static void AddMultiOption(std::string option, std::vector<T>& value, std::string describe) {
		Instance()->_options.add_options()(option.c_str(), boost::program_options::value<std::vector<T>>(&value)->multitoken(), describe.c_str());
	}
    
	/**
	 * @brief 解析，必须在添加命令（AddOption、addMultiOption）之后
	 */ 
    static void Parse(int argc, char** argv);
    
	/// @brief 输出帮助信息
    static void PrintHelp();
private:
	boost::program_options::options_description _options;
	boost::program_options::variables_map _var_map;

	DECLARE_SINGLETON(CommandOptions);
};
}
}
typedef tergeo::core::CommandOptions TergeoCmdOpts;

#endif