/**
 * @file time.h
 * @author guipp
 * @email ppgui@outlook.com
 * @date 2019-04-11
 * @par Copyright (c): 上海同辂智能科技有限公司
 * @license 核心文件，未经允许，禁止使用
 * @brief 时间、时钟
 */
#ifndef _TERGEO_COMMON_TIME_H_
#define _TERGEO_COMMON_TIME_H_
#include <chrono>
#include <thread>
#include <ctime>
#include <ros/ros.h>

#include "tergeo/common/log.h"
#include "tergeo/common/macro.h"

namespace tergeo {
namespace common {
namespace time {

using Duration = std::chrono::nanoseconds;
using TimeStamp = std::chrono::time_point<std::chrono::system_clock, Duration>;

static_assert(
    sizeof(std::chrono::nanoseconds) >= sizeof(int64_t),
    "The underlying type of the nanoseconds should be at least 64 bits.");

using nanos = std::chrono::nanoseconds;
using micros = std::chrono::microseconds;
using millis = std::chrono::milliseconds;
using seconds = std::chrono::seconds;
using minutes = std::chrono::minutes;
using hours = std::chrono::hours;

template <typename PrecisionDuration>
int64_t AsInt64(const Duration &duration) {
    return std::chrono::duration_cast<PrecisionDuration>(duration).count();
}

template <typename PrecisionDuration>
int64_t AsInt64(const TimeStamp &timestamp) {
    return AsInt64<PrecisionDuration>(timestamp.time_since_epoch());
}

inline double ToSecond(const Duration &duration) {
    return static_cast<double>(AsInt64<nanos>(duration)) * 1e-9;
}

inline double ToSecond(const TimeStamp &timestamp) {
    return static_cast<double>(AsInt64<nanos>(timestamp.time_since_epoch())) * 1e-9;
}

template <typename PrecisionDuration>
inline TimeStamp FromInt64(int64_t timestamp_value) {
    return TimeStamp(std::chrono::duration_cast<nanos>(PrecisionDuration(timestamp_value)));
}

inline TimeStamp From(double timestamp_value) {
  int64_t nanos_value = static_cast<int64_t>(timestamp_value * 1e9);
  return FromInt64<nanos>(nanos_value);
}

// in seconds
double Unix2Gps(const double unix_time_s);
double Gps2Unix(const double gps_time_s);

inline void Sleep(const int64_t milli_second) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milli_second));
}
inline void SleepMicroSeconds(const int64_t micro_second) {
    std::this_thread::sleep_for(std::chrono::microseconds(micro_second));
}
namespace private_clock {
class BaseClock {
public:
    BaseClock() = default;
    virtual ~BaseClock() = default;
    
    virtual ros::Time rosTime() const = 0;
    virtual TimeStamp now() const = 0;
    virtual double nowInSeconds() const = 0;
    virtual int64_t nowInMicroSeconds() const = 0;
    virtual int64_t nowInMilliSeconds() const = 0;
};
class SystemClock : public BaseClock {
public:
    SystemClock() = default;
    virtual ~SystemClock() = default;
    virtual ros::Time rosTime() const  {
        return ros::Time(nowInSeconds());
    }
    virtual TimeStamp now() const {
        return std::chrono::time_point_cast<Duration>(std::chrono::system_clock::now());
    }
    virtual double nowInSeconds() const {
        TimeStamp ts = std::chrono::time_point_cast<Duration>(std::chrono::system_clock::now());
        return static_cast<double>(AsInt64<nanos>(ts.time_since_epoch())) * 1e-9;
    }
    virtual int64_t nowInMicroSeconds() const {
        TimeStamp ts = std::chrono::time_point_cast<Duration>(std::chrono::system_clock::now());
        return AsInt64<micros>(ts.time_since_epoch());
    }
    virtual int64_t nowInMilliSeconds() const {
        TimeStamp ts = std::chrono::time_point_cast<Duration>(std::chrono::system_clock::now());
        return AsInt64<millis>(ts.time_since_epoch());
    }
};
class RosClock : public BaseClock {
public:
    RosClock() = default;
    virtual ~RosClock() = default;

    virtual ros::Time rosTime() const  {
        return ros::Time::now();
    }
    virtual TimeStamp now() const {
        return From(nowInSeconds());
    }
    virtual double nowInSeconds() const {
        return ros::Time::now().toSec();
    }
    virtual int64_t nowInMicroSeconds() const {
        return ros::Time::now().toNSec() * 1e-3;
    }
    virtual int64_t nowInMilliSeconds() const {
        return ros::Time::now().toNSec() * 1e-6;
    }
};
}

//
class Clock final {
public:
    static constexpr int64_t PRECISION =
        std::chrono::system_clock::duration::period::den /
        std::chrono::system_clock::duration::period::num;

    /// PRECISION >= 1000000 means the precision is at least 1us.
    static_assert(PRECISION >= 1000000,
            "The precision of the system clock should be at least 1 "
            "microsecond.");

    enum ClockMode {
        SYSTEM = 0,
        ROS = 1
    };
    static ros::Time RosTime() {return Instance()->_base_clock->rosTime();}

    static TimeStamp Now() {return Instance()->_base_clock->now();}
    // us
    static int64_t NowInMicroSeconds() {return Instance()->_base_clock->nowInMicroSeconds();}
    // ms
    static int64_t NowInMilliSeconds() {return Instance()->_base_clock->nowInMilliSeconds();}
    
    static double NowInSeconds() { return Instance()->_base_clock->nowInSeconds(); }

    static void SetMode(ClockMode mode) {Instance()->setMode(mode);}
    static ClockMode GetMode() { return Instance()->_mode; }
    
    static std::string NowToString() {
        std::time_t tt = std::chrono::system_clock::to_time_t(Now());
        struct tm *local;
        local = std::localtime(&tt);
        char time_ch[200];
        size_t size = std::strftime(time_ch, sizeof(time_ch), "%Y%m%d-%H%M%S", local);
        return std::string(time_ch);
    }
 private:
    void setMode(ClockMode mode);
    ClockMode _mode;
    std::shared_ptr<private_clock::BaseClock> _base_clock;
    DECLARE_SINGLETON(Clock);
};

}
}
}
#endif