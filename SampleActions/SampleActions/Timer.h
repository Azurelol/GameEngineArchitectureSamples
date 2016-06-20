#pragma once


#include <chrono>

namespace Time {
  //----------------------------------------------------------------------------/
  // A framework that relates a time point to real physical time
  using clock = std::chrono::high_resolution_clock;
  // A reference to a specific point in time, like one's birthday, etc
  //  high_resolution_clock is the clock with the shortest tick period
  using timePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
  // Durations measure time spans, like one minute, two hours, ten ms
  using floatSeconds = std::chrono::duration<float>;
  //----------------------------------------------------------------------------/

  class ScopeTimer {
  public:
    ScopeTimer(float* output) : StartTime(clock::now()), _RetVal(output) {}
    ~ScopeTimer() {
      EndTime = Time::clock::now();
      Time::floatSeconds duration = EndTime - StartTime;
      *_RetVal = duration.count();

    }

  private:
    Time::timePoint StartTime;
    Time::timePoint EndTime;
    float* _RetVal;
  };
}