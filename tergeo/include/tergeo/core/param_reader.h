/**
 * @file param_reader.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 参数文件读取,参数格式定义与proto文件类似，
 *        注：必须每行只有一个参数
 *        每行形式 key:value 或 key: [v1, v2. v3]
 *        支持 以 "#" 注释
 *        自动跳过空格行
 */
#ifndef _TERGEO_CORE_PARAM_READER_H
#define _TERGEO_CORE_PARAM_READER_H

#include "tergeo/common/log.h"
#include <memory>
#include <vector>

namespace tergeo {
namespace common {

class ParamReaderPrivate;
/// @brief 参数文件读取
class ParamReader final {
public:
    typedef std::shared_ptr<ParamReader> Ptr;
    ParamReader();
    explicit ParamReader(const std::string file_path, bool case_sensitive = false);
    ~ParamReader();
    /**
     * @brief 索引值是否大小写敏感
     * @param ture: 区分大小写
     *        false: 不区分大小写，Key、KEY等同 
     */ 
    void setKeyCaseSensitive(bool case_sensitive);
    /**
     * @brief 加载参数文件
     * @param input 参数文件路径名
     * @param input 是否采用追加方式，
     *              ture: 不清空当前已经读取的值，适用于从多文件读取参数
     *              false: 清空当已经读取的值，单文件读取
     * @return 返回是否读取成功 
     */ 
    bool loadParam(const std::string& file_path, bool append = false);
    bool saveParam(const std::string& file_path);
    bool has(const std::string& key) const;

    template <class T>
    bool getValue(const std::string& key, T& value) {
        if (!has(key)) {
            return false;
        }
        std::stringstream ss(getStringValue(key));
        ss >> value;
        return true;
    }
    template <class T>
    bool getValueVec(const std::string& key, std::vector<T>& values) {
        if (!has(key)) {
            return false;
        }
        values.clear();
        std::stringstream ss(getStringValue(key));
        T value;
        while (ss >> value) {
            values.push_back(value);
        }
        return true;
    }
    template <class T>
    bool setValue(std::string key, T value) {
        std::stringstream ss;
        ss << value;
        return setStringValue(key, ss.str());
    }
    template <class T>
    bool setValueVec(std::string key, std::vector<T>& values) {
        std::stringstream ss;
        if (values.empty()) {
            AERROR << "Values vec empty!";
            return false;
        }
        ss << values[0];
        for (int i = 1; i < values.size(); ++i) {
            ss << " " << values[i];
        }
        return setStringValue(key, ss.str());
    }

private:
    std::string getStringValue(const std::string& key) const;
    bool setStringValue(std::string key, std::string value);

private:
    ParamReaderPrivate* _ptr = nullptr;
};


}
}
#endif
