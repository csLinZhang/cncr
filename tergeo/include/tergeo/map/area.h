#ifndef _TERGEO_MAP_AREA_H
#define _TERGEO_MAP_AREA_H

#include "tergeo/common/common.hpp"
#include "tergeo/map/proto/area.pb.h"
#include "tergeo/map/point_feature.h"
#include "tergeo/map/line_feature.h"
#include "tergeo/map/polyline_feature.h"
#include "tergeo/map/polygon_feature.h"
#include "tergeo/map/kd_tree.h"
namespace tergeo {
namespace map {
using SignalTable = std::unordered_map<std::string, std::unique_ptr<Signal> >;
using TreeTable = std::unordered_map<std::string, std::unique_ptr<Tree> >;
using StopSignTable = std::unordered_map<std::string, std::unique_ptr<StopSign> >;
using SpeedBumpTable = std::unordered_map<std::string, std::unique_ptr<SpeedBump> >;
using RoadEdgeTable = std::unordered_map<std::string, std::unique_ptr<RoadEdge> >;
using LaneLineTable = std::unordered_map<std::string, std::unique_ptr<LaneLine> >;
using CrosswalkTable = std::unordered_map<std::string, std::unique_ptr<Crosswalk> >;
using JunctionTable = std::unordered_map<std::string, std::unique_ptr<Junction> >;
using ClearAreaTable = std::unordered_map<std::string, std::unique_ptr<ClearArea> >;
using ParkingSpaceTable = std::unordered_map<std::string, std::unique_ptr<ParkingSpace> >;
using RoadTable = std::unordered_map<std::string, std::unique_ptr<Road> >;

class Area {
    DECLARE_DEFAULT_STRUCTOR(Area)
public:
    DECLARE_SHARED_PTR(Area)
    bool load(const std::string file_name);
    
    std::string getName() const;
    const common::math::Rect2d& getBoundingRect() const;
    const proto::Area& getProtoArea() const;
    
    bool isPointIn(const double X, const double Y) const;
    // return nullptr if not found 
    const Signal* getSignalByID(const std::string& id) const;
    const Tree* getTreeByID(const std::string& id) const;
    const StopSign* getStopSignByID(const std::string& id) const;
    const SpeedBump* getSpeedBumpByID(const std::string& id) const;
    const RoadEdge* getRoadEdgeByID(const std::string& id) const;
    const LaneLine* getLaneLineByID(const std::string& id) const;
    const Crosswalk* getCrosswalkByID(const std::string& id) const;
    const Junction* getJunctionByID(const std::string& id) const;
    const ClearArea* getClearAreaByID(const std::string& id) const;
    const ParkingSpace* getParkingSpaceByID(const std::string& id) const;
    const Road* getRoadByID(const std::string& id) const;
    const Road* getRoadByPosition(const double X, const double Y) const;

    // return size of vec<>
    int getSignals(const common::math::Point2d& point, const float radius,
           std::vector<const Signal*>& signal_lamps) const;
    int getTrees(const common::math::Point2d& point, const float radius,
           std::vector<const Tree*>& trees) const;
    int getStopSigns(const common::math::Point2d& point, const float radius,
           std::vector<const StopSign*>& stop_signs) const;
    int getSpeedBumps(const common::math::Point2d& point, const float radius,
           std::vector<const SpeedBump*>& speed_bumps) const;    
    int getRoadEdges(const common::math::Point2d& point, const float radius,
           std::vector<const RoadEdge*>& road_edges) const;    
    int getLaneLines(const common::math::Point2d& point, const float radius,
           std::vector<const LaneLine*>& lane_lines) const;    
    int getCrosswalks(const common::math::Point2d& point, const float radius,
           std::vector<const Crosswalk*>& crosswalks) const;    
    int getJunctions(const common::math::Point2d& point, const float radius,
           std::vector<const Junction*>& junctions) const;    
    int getClearAreas(const common::math::Point2d& point, const float radius,
           std::vector<const ClearArea*>& clear_areas) const;    
    int getParkingSpaces(const common::math::Point2d& point, const float radius,
           std::vector<const ParkingSpace*>& parking_spaces) const;    
    int getRoads(const common::math::Point2d& point, const float radius,
           std::vector<const Road*>& roads) const;

    //////
    static int Load(const std::string map_path = "");
    static const Area* GetArea(const std::string name);
    static const Area* GetArea(const double X, const double Y);
    static std::vector<std::string> getAreaNames();
private:
    void buildSignalTree();
    void buildTreeTree();
    void buildStopSignTree();
    void buildSpeedBumpTree();
    void buildRoadEdgeTree();
    void buildLaneLineTree();
    void buildCrosswalkTree();
    void buildJunctionTree();
    void buildClearAreaTree();
    void buildParkingSpaceTree();
    void buildRoadTree();

    void computeBoundingBox();
private:
    proto::Area _proto_area;
    bool _is_init = false;
    std::string _name;
    common::math::Rect2d _bounding_rect;

    SignalTable _signal_table;
    TreeTable _tree_table;
    StopSignTable _stop_sign_table;
    SpeedBumpTable _speed_bump_table;
    RoadEdgeTable _road_edge_table;
    LaneLineTable _lane_line_table;
    CrosswalkTable _crosswalk_table;
    JunctionTable _junction_table;
    ClearAreaTable _clear_area_table;
    ParkingSpaceTable _parking_space_table;
    RoadTable _road_table;

    KDTree _signal_tree;
    KDTree _tree_tree;
    KDTree _stop_sign_tree;
    KDTree _speed_bump_tree;
    KDTree _road_edge_tree;
    KDTree _lane_line_tree;
    KDTree _crosswalk_tree;
    KDTree _junction_tree;
    KDTree _clear_area_tree;
    KDTree _parking_space_tree;
    KDTree _road_tree;
};

}
}

#endif