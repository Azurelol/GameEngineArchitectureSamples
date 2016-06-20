/******************************************************************************/
/*!
@file   Timer.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   2/21/2016
@copyright Copyright 2016, DigiPen Institute of Technology. All rights reserved.
*/
/******************************************************************************/
#include "Timer.h"

#include "Engine.h"

namespace SPEngine{
  namespace Time {

    /**************************************************************************/
    /*!
    @brief Timer constructor.
    @param duration How long should the timer run for. If set to 0, it will go
           indefinitely or until it hits 0 (if stopwatch)
    @param mode What mode will the timer use. A stopwatch will count down from
           the given duration, while the timer will count up to the given duration.
    @param reset Whether the timer should reset after hitting the duration.
    */
    /**************************************************************************/
    Timer::Timer(float duration, Mode mode, bool reset) : CurrentTime(0.0f), Duration(duration), CurrentMode(mode), Reset(reset)
    {
      if (CurrentMode == Mode::StopWatch)
        CurrentTime = Duration;
    }

    /**************************************************************************/
    /*!
    @brief Updates the Timer directly through the Engine.
    @return True if the timer hit its specified time, false otherwise.
    */
    /**************************************************************************/
    bool Timer::Update() {
      return Update(Engine::Dt());
    }

    /**************************************************************************/
    /*!
    @brief Updates the Timer off a delta time.
    @param dt The delta time.
    @return True if the timer hit its specified time, false otherwise.
    */
    /**************************************************************************/
    bool Timer::Update(float dt)
    {
      if (CurrentMode == Mode::Countdown) {

        if (CurrentTime >= Duration) {
          if (Reset)
            CurrentTime = 0.0f;
          return true;
        }

        CurrentTime += dt;
      }
      else if (CurrentMode == Mode::StopWatch) {

        if (CurrentTime <= 0.0f) {
          if (Reset)
            CurrentTime = Duration;
          return true;
        }

        CurrentTime -= dt;
      }

      // Neither of the conditions have been met
      return false;

    }

    void FunctionTimer::Record()
    {
      EndTime = Time::clock::now();
      ElapsedTime = Time::floatSeconds(EndTime - StartTime).count();
    }

  }
}