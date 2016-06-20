/******************************************************************************/
/*!
@file   Timer.h
@author Allan Deutsch, Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   7/30/2015
@brief  Includes some basic timers.
*/
/******************************************************************************/
#pragma once

namespace Utils {

  namespace Time {

    // A framework that relates a time point to real physical time
    using clock = std::chrono::high_resolution_clock;
    // A reference to a specific point in time, like one's birthday, etc
    //  high_resolution_clock is the clock with the shortest tick period
    using timePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using ms = std::chrono::milliseconds;
    using us = std::chrono::microseconds;
    // Durations measure time spans, like one minute, two hours, ten ms
    using floatSeconds = std::chrono::duration<float>;

    class ScopeTimer {
    public:
      /**************************************************************************/
      /*!
      \brief
      The constructor..
      \param output
      A pointer to a float.
      */
      /**************************************************************************/
      ScopeTimer(float* output) : StartTime(Time::clock::now()), _RetVal(output) {}

      /**************************************************************************/
      /*!
      \brief
      The destructor. When the timer leaves the scope, gets the end time. It then
      converts the duration to a float where 1.0f == 1 second.
      It then stores the result in a pointer given at initialization.
      */
      /**************************************************************************/
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


}