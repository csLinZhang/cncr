#ifndef _TERGEO_PERCEPTION_SHARED_DATA_FUSIOTN_H
#define _TERGEO_PERCEPTION_SHARED_DATA_FUSIOTN_H
#include "tergeo/perception/utils.h"
#include "tergeo/perception/global_data.h"
#include "tergeo/common/thread/thread_pool.h"

namespace tergeo {
namespace perception {
template<typename M1 = NullType, typename M2 = NullType,
    typename M3 = NullType, typename M4 = NullType>
class SharedDataFusion {
    DECLARE_DEFAULT_STRUCTOR(SharedDataFusion)
protected:
    void initFusionSharedData(const std::vector<Edge>& edges) {
        CHECK(edges.size() == 4) << "edge size not equal 4";
        _shared_data_list_1 = GlobalData::Instance()->getSharedDataList<M1>(edges[0]);
        _shared_data_list_2 = GlobalData::Instance()->getSharedDataList<M2>(edges[1]);
        _shared_data_list_3 = GlobalData::Instance()->getSharedDataList<M3>(edges[2]);
        _shared_data_list_4 = GlobalData::Instance()->getSharedDataList<M4>(edges[3]);
    }
    
    bool fusion(const double& sync_time_interval_s) {
        typename SharedDataList<M1>::StampData msg_1;
        if (!_shared_data_list_1->getLatestData(msg_1)) {
            AWARN << "Empty shared data list";
            return false;
        }
        typename SharedDataList<M2>::StampData msg_2;
        if (!_shared_data_list_2->getLatestData(msg_2)) {
            AWARN << "Empty shared data list";
            return false;
        }
        typename SharedDataList<M3>::StampData msg_3;
        if (!_shared_data_list_3->getLatestData(msg_3)) {
            AWARN << "Empty shared data list";
            return false;
        }
        typename SharedDataList<M4>::StampData msg_4;
        if (!_shared_data_list_4->getLatestData(msg_4)) {
            AWARN << "Empty shared data list";
            return false;
        }
        if (sync_time_interval_s > 0) {
            double max_time = std::max(std::max(msg_1.first, msg_2.first), 
                std::max(msg_3.first, msg_4.first));
            double min_time = std::min(std::min(msg_1.first, msg_2.first), 
                std::min(msg_3.first, msg_4.first));
            if (max_time - min_time > sync_time_interval_s) {
                AWARN << "Sync data timeout: " << max_time - min_time <<
                    " Expect less than: " << sync_time_interval_s; 
                return false;
            }
        }
        tergeo::common::ThreadPool::Instance()->schedule(
            std::bind(&SharedDataFusion<M1, M2, M3, M4>::proc, this, 
            *(msg_1.second), *(msg_2.second), *(msg_3.second), *(msg_4.second)));
        return true;
    }
    
    virtual void proc(const M1& msg_1, const M2& msg_2, const M3& msg_3, const M4& msg_4) = 0;
  
private:
    SharedDataList<M1>* _shared_data_list_1 = nullptr;
    SharedDataList<M2>* _shared_data_list_2 = nullptr;
    SharedDataList<M3>* _shared_data_list_3 = nullptr;
    SharedDataList<M4>* _shared_data_list_4 = nullptr;
};

template<typename M1>
class SharedDataFusion<M1, NullType, NullType, NullType> {
    DECLARE_DEFAULT_STRUCTOR(SharedDataFusion)

protected:
    void initFusionSharedData(const std::vector<Edge>& edges) {
        CHECK(edges.size() == 1) << "edge size not equal 1";
        _shared_data_list_1 = GlobalData::Instance()->getSharedDataList<M1>(edges[0]);
    }
    
    bool fusion(const double& sync_time_interval_s) {
        typename SharedDataList<M1>::StampData msg_1;
        if (!_shared_data_list_1->getLatestData(msg_1)) {
            AWARN << "Empty shared data list";
            return false;
        }
        tergeo::common::ThreadPool::Instance()->schedule(
            std::bind(&SharedDataFusion<M1>::proc, this, *(msg_1.second)));
        return true;
    }
    
    virtual void proc(const M1& msg_1) = 0;
  
private:
    SharedDataList<M1>* _shared_data_list_1 = nullptr;
};

template<typename M1, typename M2>
class SharedDataFusion<M1, M2, NullType, NullType> {
    DECLARE_DEFAULT_STRUCTOR(SharedDataFusion)

protected:
    void initFusionSharedData(const std::vector<Edge>& edges) {
        CHECK(edges.size() == 2) << "edge size not equal 2";
        _shared_data_list_1 = GlobalData::Instance()->getSharedDataList<M1>(edges[0]);
        _shared_data_list_2 = GlobalData::Instance()->getSharedDataList<M2>(edges[1]);
    }
    
    bool fusion(const double& sync_time_interval_s) {
        typename SharedDataList<M1>::StampData msg_1;
        if (!_shared_data_list_1->getLatestData(msg_1)) {
            AWARN << "Empty shared data list";
            return false;
        }
        typename SharedDataList<M2>::StampData msg_2;
        if (!_shared_data_list_2->getLatestData(msg_2)) {
            AWARN << "Empty shared data list";
            return false;
        }
        if (sync_time_interval_s > 0) {
            if (std::abs(msg_1.first - msg_2.first) > sync_time_interval_s) {
                AWARN << "Sync data timeout: " << std::abs(msg_1.first - msg_2.first) <<
                    " Expect less than: " << sync_time_interval_s; 
                return false;
            }
        }
        tergeo::common::ThreadPool::Instance()->schedule(
            std::bind(&SharedDataFusion<M1, M2>::proc, this, 
            *(msg_1.second), *(msg_2.second)));
        return true;
    }
    virtual void proc(const M1& msg_1, const M2& msg_2) = 0;
  
private:
    SharedDataList<M1>* _shared_data_list_1 = nullptr;
    SharedDataList<M2>* _shared_data_list_2 = nullptr;
};

template<typename M1, typename M2, typename M3>
class SharedDataFusion<M1, M2, M3, NullType> {
    DECLARE_DEFAULT_STRUCTOR(SharedDataFusion)

protected:
    void initFusionSharedData(const std::vector<Edge>& edges) {
        CHECK(edges.size() == 3) << "edge size not equal 3";
        _shared_data_list_1 = GlobalData::Instance()->getSharedDataList<M1>(edges[0]);
        _shared_data_list_2 = GlobalData::Instance()->getSharedDataList<M2>(edges[1]);
        _shared_data_list_3 = GlobalData::Instance()->getSharedDataList<M3>(edges[2]);
    }
    
    bool fusion(const double& sync_time_interval_s) {
        typename SharedDataList<M1>::StampData msg_1;
        if (!_shared_data_list_1->getLatestData(msg_1)) {
            AWARN << "Empty shared data list";
            return false;
        }
        typename SharedDataList<M2>::StampData msg_2;
        if (!_shared_data_list_2->getLatestData(msg_2)) {
            AWARN << "Empty shared data list";
            return false;
        }
        typename SharedDataList<M3>::StampData msg_3;
        if (!_shared_data_list_3->getLatestData(msg_3)) {
            AWARN << "Empty shared data list";
            return false;
        }
        if (sync_time_interval_s > 0) {
            double max_time = std::max(std::max(msg_1.first, msg_2.first), msg_3.first);
            double min_time = std::min(std::min(msg_1.first, msg_2.first), msg_3.first);
            if (max_time - min_time > sync_time_interval_s) {
                AWARN << "Sync data timeout: " << max_time - min_time <<
                    " Expect less than: " << sync_time_interval_s; 
                return false;
            }
        }
        tergeo::common::ThreadPool::Instance()->schedule(
            std::bind(&SharedDataFusion<M1, M2, M3>::proc, this, 
            *(msg_1.second), *(msg_2.second), *(msg_3.second)));
        return true;
    }
    virtual void proc(const M1& msg_1, const M2& msg_2, const M3& msg_3) = 0;
  
private:
    SharedDataList<M1>* _shared_data_list_1 = nullptr;
    SharedDataList<M2>* _shared_data_list_2 = nullptr;
    SharedDataList<M3>* _shared_data_list_3 = nullptr;
};

}
}

#endif