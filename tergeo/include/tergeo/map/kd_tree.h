#ifndef _TERGEO_HD_MAP_KD_TREE_H
#define _TERGEO_HD_MAP_KD_TREE_H
#include "tergeo/common/common.hpp"

namespace tergeo {
namespace map {
class KDTreePrivate;
class KDTree final {
public:
    KDTree();
    ~KDTree();

    void addPoints(const std::string id, 
        const std::vector<common::math::Point2d>& points);
    void build();
    
    int radiusSearch(const common::math::Point2d& point, 
        const float radius, std::vector<std::string>& ids) const;
private:
    KDTreePrivate* _ptr = nullptr;    
};
}
}

#endif
