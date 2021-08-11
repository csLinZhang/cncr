#ifndef _TERGEO_MAP_POITN_FEATURE_H
#define _TERGEO_MAP_POITN_FEATURE_H

#include "tergeo/common/math/point.h"
#include "tergeo/map/proto/point_feature.pb.h"

namespace tergeo {
namespace map {

class PointFeature {
public:
    PointFeature() = default;
    virtual ~PointFeature() = default;
    
    const common::math::Point2d& getPoint() const;
    
protected:
    common::math::Point2d _point; 
};

class Signal : public PointFeature {
public:
    Signal() = default;
    ~Signal() = default;

    Signal(const proto::Signal& proto_signal);
    
    std::string id() const;
    double getHeight() const;
    void setProtoSignal(const proto::Signal& proto_signal);
    const proto::Signal& getProtoSignal() const;
private:
    proto::Signal _proto_signal;
};

class Tree : public PointFeature {
public:
    Tree() = default;
    ~Tree() = default;

    Tree(const proto::Tree& proto_tree);
    
    std::string id() const;
    void setProtoTree(const proto::Tree& proto_tree);
    const proto::Tree& getProtoTree() const;
private:
    proto::Tree _proto_tree;
};

}
}

#endif