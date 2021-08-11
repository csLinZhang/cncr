#ifndef _TERGEO_PIPELINE_PIPELINE_CLIENT_H
#define _TERGEO_PIPELINE_PIPELINE_CLIENT_H

#include "tergeo/common/common.hpp"
#include "tergeo/pipeline/proto/task.pb.h"

namespace tergeo {
namespace pipeline {

using TaskList = std::vector<proto::Task>;

class PipelineClient final {
public:
    virtual ~PipelineClient() = default;

    static bool GetCurrentTaskStatus(int& task_status);
    static bool SetCurrentTaskStatus(int task_status); 

    static bool GetCurrentTask(proto::Task& task);
    static bool GetTask(const std::string& id, proto::Task& task);
    static bool GetNextTask(proto::Task& task);

    static TaskList GetAllTasks();

    static bool RemoveTask(const std::string& id);
    
    static bool AddTask(const proto::Task& task); 
    
    static bool LoadTasks(const std::string& filename);
private:
    DECLARE_SINGLETON(PipelineClient)
};

}
} // namespace tergeo 

#endif