#ifndef _TERGEO_PIPELINE_PIPELINE_SERVICE_H
#define _TERGEO_PIPELINE_PIPELINE_SERVICE_H

#include "tergeo/common/common.hpp"

namespace tergeo {
namespace pipeline {
class PipelineServicePrivate;
class PipelineService final {
public:
    PipelineService();
    virtual ~PipelineService();
    
    bool init();
    bool load(const std::string filename);
private:
    PipelineServicePrivate* _ptr = nullptr;
};

}
}
#endif