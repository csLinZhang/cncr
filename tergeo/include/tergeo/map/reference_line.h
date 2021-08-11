#ifndef _TERGEO_MAP_REFERENCE_LINE_H
#define _TERGEO_MAP_REFERENCE_LINE_H
#include "tergeo/common/common.hpp"

namespace tergeo {
namespace map {

class ReferenceLinePoint final : public tergeo::common::math::Pose2d {
public:
    ReferenceLinePoint() : tergeo::common::math::Pose2d(), action_flag(0) {

    }
    ReferenceLinePoint& operator=(const ReferenceLinePoint& other) {
        if (this == &other) {
            return *this;
        }
        this->x = other.x;
        this->y = other.y;
        this->theta = other.theta;
        this->action_flag = other.action_flag;
        return *this;
    }

public: 
    int action_flag;
};

class ReferenceLine final {
public:
    DECLARE_SHARED_PTR(ReferenceLine)
    ReferenceLine() = default;   
    ~ReferenceLine() = default;

    bool load(const std::string& filename);
    
    std::string getName() const {return _name;}
    const std::vector<ReferenceLinePoint>& getPoints() const {return _points;} 

    void setName(const std::string name) {_name = name;}
    void setPoints(const std::vector<ReferenceLinePoint>& points);
    ReferenceLine& operator=(const ReferenceLine& other);

    //////////
    static int Load(const std::string ref_path = "");
    static const ReferenceLine* GetReferenceLine(const std::string name);
    static std::vector<std::string> getReferenceLineNames();
private:
    std::string _name;
    std::vector<ReferenceLinePoint> _points;
};

}
}

#endif 

