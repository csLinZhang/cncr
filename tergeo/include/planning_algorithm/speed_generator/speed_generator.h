#ifndef _TERGEO_PLANNING_ALGORITHM_SPEED_GENERATOR_H_
#define _TERGEO_PLANNING_ALGORITHM_SPEED_GENERATOR_H_

#include <vector>

namespace tergeo{
namespace planning{
namespace algorithm{

struct KinematicLimits{
    double max_v;
    double max_a;
    double max_jerk;
};
struct PoseVT {
    double x;
    double y;
    double theta;
    double v;
    double relative_time;
};

typedef std::vector<PoseVT> Trajectory;

class SpeedGenerator{
public:
    SpeedGenerator(){};
    virtual ~SpeedGenerator(){}
    //set conditions separately.
    void setStartVel(const double& vel){_v0 = vel;}
    void setEndVel(const double& vel){_vf = vel;}
    void setStartAcc(const double& a){_a0 = a;}
    void setEndAcc(const double& a){_af = a;}
    void setTrajLength(const double& s){_sf = s;}
    //set conditions all in one.
    void setConditions(double v0, double vf, double a0, double af, double sf){
        _v0 = v0;
        _a0 = a0;
        _vf = vf;
        _af = af;
        _sf = sf;
    }
    void setKinematicLimit(const KinematicLimits& limit){
        _limit = limit;
    }
    virtual void genSpeedProfile(const Trajectory&ori_traj,
                                 Trajectory& traj_with_speed) = 0;
protected:
    //初始点速度,加速度,结束点速度,加速度,路径长度 
    double _a0,_af,_v0,_vf,_sf;
    KinematicLimits _limit;
};

//reference paper: focused trajectory planning for autonomous on-road driving
//问题：没有运动限制，比如最大速度及最大加速度等
class SplineSpeedGenerator:public SpeedGenerator{
public:
    SplineSpeedGenerator(){}
    ~SplineSpeedGenerator(){}
    virtual void genSpeedProfile(const Trajectory&ori_traj,
                                Trajectory& traj_with_speed);
private:
    void solve();
private:
    struct CostFunctor {
        CostFunctor(double v0,double a0,double vf,double af,double sf)
        :_v0(v0),_a0(a0),_vf(vf),_af(af),_sf(sf){}
        template<typename T> bool operator()(const T* const q,T* residual) const {
            residual[0] = T(q[0] - T(_v0));
            residual[1] = T(q[1] - T(_a0));
            residual[2] = T(q[0]+q[1]*q[4]+q[2]*q[4]*q[4]+q[3]*q[4]*q[4]*q[4]-T(_vf));
            residual[3] = T(q[1] + T(2) * q[2] * q[4] + T(3)*q[3]*q[4]*q[4]-T(_af));
            residual[4] = T(q[0]*q[4]+ T(1.0 / 2) * q[1] * q[4] + T(1.0 / 3) 
                * q[2]*q[4]*q[4]*q[4] + T(1.0/4)*q[3]*q[4]*q[4]*q[4]*q[4]-T(_sf));
            return true;
       }
    private:
       double _v0, _a0, _vf, _af, _sf;
    };
    //由s反解t
    struct STCost{
        STCost(double s, double* q):_s(s), _q(q){}
        template<typename T> bool operator()(const T* const t, T* residual) const {
            //st = q0*t+1/2*q1*t^2+1/3*q2*t^3+1/4*q3*t^4.
            residual[0] = T(_q[0]*t[0]+T(1.0/2)*_q[1]*t[0]*t[0]
                +T(1.0/3)*_q[2]*t[0]*t[0]*t[0]+T(1.0/4)*_q[3]*t[0]*t[0]*t[0]*t[0]-_s);
            return true;
        }
    private:
        double _s;
        double* _q;
    };
private:
    double _q0, _q1, _q2, _q3, _tf;
};

class TShapeSpeedGenerator:  public SpeedGenerator{
public:
    TShapeSpeedGenerator(){}
    ~TShapeSpeedGenerator(){}
    virtual void genSpeedProfile(const Trajectory&ori_traj,
                                Trajectory& traj_with_speed);
};

class SShapeSpeedGenerator: public SpeedGenerator{
public:
    SShapeSpeedGenerator(){}
    ~SShapeSpeedGenerator(){}
    virtual void genSpeedProfile(const Trajectory&ori_traj,
                                Trajectory& traj_with_speed);
};
}
} // namespace plugin
} // namespace tergeo

#endif