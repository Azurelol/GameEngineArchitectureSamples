#pragma once

#include <iostream>
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

/*===================*
*     Trace         *
*===================*/
// Traces using the function'ss signature as the prefix
#define Trace(message) std::cout << __FUNCTION__ << ": " << message << "\n"
// Traces using the Object's name and the function's signature as the prefix
#define TraceObject(message) std::cout << "[" << getName() << "] " << __FUNCTION__ << ": " << message << "\n"

#define FORWARD_DECLARE(className) class className

/*===================*
*     Properties     *
*===================*/
// This macro creates the definitions of getter and setter method for a Property.
#define DEFINE_PROPERTY(propertyType, propertyName)                           \
  const propertyType& get##propertyName() const {                                 \
    return propertyName;                                                          \
  }                                                                               \
  void set##propertyName(propertyType const& value) {                             \
    propertyName = value;                                                         \
  }

#define DEFINE_PROPERTY_PTR(propertyType, propertyName)                           \
  const propertyType get##propertyName() const {                                 \
    return propertyName;                                                          \
  }                                                                               \
  void set##propertyName(propertyType const value) {                             \
    propertyName = value;                                                         \
  }

// This macro creates the definitions of a getter method for a Property.
#define DEFINE_GETTER(propertyType, propertyName)                             \
  const propertyType& get##propertyName() const {                                 \
    return propertyName;                                                          \
  }
// This macro creates the definitions of a setter method for a Property.
#define DEFINE_SETTER(propertyType, propertyName)                             \
  void set##propertyName(propertyType const& value) {                             \
    propertyName = value;                                                         \
  }