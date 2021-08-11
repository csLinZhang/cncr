#ifndef _TERGEO_PLUGIN_OPERATION_BASE_CLOUD_FILTER_H
#define _TERGEO_PLUGIN_OPERATION_BASE_CLOUD_FILTER_H

#include "tergeo/common/common.hpp"
#include "tergeo/core/factory.h"
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace tergeo {
namespace plugin {
namespace operation {

class BaseCloudFilter : public tergeo::core::IPlugin {
    DECLARE_FACTORY(BaseCloudFilter)
    DECLARE_DEFAULT_STRUCTOR(BaseCloudFilter)
public:    
    virtual bool init() = 0;
    
    virtual bool filter(const pcl::PointCloud<pcl::PointXYZ>& cloud_in, 
                        pcl::PointCloud<pcl::PointXYZ>& cloud_out) const = 0;
    virtual bool filter(const pcl::PointCloud<pcl::PointXYZI>& cloud_in, 
                        pcl::PointCloud<pcl::PointXYZI>& cloud_out) const = 0;
    virtual bool filter(const pcl::PointCloud<pcl::PointXYZRGB>& cloud_in, 
                        pcl::PointCloud<pcl::PointXYZRGB>& cloud_out) const = 0;
};

#define REGISTER_CLOUD_FILTER_CLASS_CPP(sub_class) \
    REGISTER_CLASS_CPP(tergeo::plugin::operation::BaseCloudFilter, sub_class)

}
}
}

#endif