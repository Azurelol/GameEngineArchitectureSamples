/*****************************************************************************/
/*!
@file   Profiler.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/25/2016
*/
/******************************************************************************/
#include "Profiler.h"
#include "Engine.h"


namespace SPEngine
{
  /**************************************************************************/
/*!
@brief Adds a time to the specified container, making sure its aggregated.
@param container A reference to the container.
@param time A reference to the timeslice object.
*/
/**************************************************************************/
  void Profiler::AddSystemTime(Time::FunctionProfileContainer & container, Time::FunctionProfile & time)
  {
    // Attempt to look for a matching time slice in the container
    auto matchingTime = std::find_if(container.begin(), container.end(),
      [=](Time::FunctionProfile& t) {
      return t.Name == time.Name;
    });
    // If it's there, add this time to it
    if (matchingTime != container.end()) {
      matchingTime->Time += time.Time;
      matchingTime->Calls++;
    }
    // Else, add it to the container
    else {
      container.push_back(time);
    }
  }

  /**************************************************************************/
  /*!
  @brief Adds a system's time to the profiler.
  @param systemTime The system and the time elapsed during its udpate method.
  */
  /**************************************************************************/
  void Profiler::Add(const Time::FunctionProfile profile, std::string category) 
  {
    // Look for the right container of profiles matching the given category
    auto& map = Profiles[category]; 
    // Add the profile to it
    map.Add(profile);
  }

  /**************************************************************************/
  /*!
  @brief Adds a system method to the profiler.
  @param tiime The method and the time elapsed during its execution.
  */
  /**************************************************************************/
  void Profiler::Add(Time::FunctionProfile time, Systems::Enumerated system) 
  {
    SystemProfiles[system].Add(time);
  }

  /**************************************************************************/
  /*!
  @brief Clear.
  */
  /**************************************************************************/
  void Profiler::Clear()
  {
    for (auto& profile : Profiles) {
      profile.second.Update();
    }

    for (auto& profile : SystemProfiles) {
      profile.second.Update();
    }
  }

  /**************************************************************************/
  /*!
  @brief Returns the engine's FPS.
  @return The engine's FPS.
  */
  /**************************************************************************/
  float Profiler::FPS()
  {
    return CurrentFPS;
  }

  /**************************************************************************/
  /*!
  @brief Updates the profiler
  @param dt The delta time.
  */
  /**************************************************************************/
  void Profiler::Update(float dt)
  {
    CalculateFPS(dt);
    Clear();
  }

  /**************************************************************************/
  /*!
  @brief Returns a container of the profiles of the given category.
  @param category The name of the category of times.
  @return A container of FunctionProfiles.
  */
  /**************************************************************************/
  Time::FunctionProfileContainer & Profiler::Times(std::string category)
  {
    return Profiles.at(category).Time();
  }

  /**************************************************************************/
  /*!
  @brief Returns a container of the profiles of the given category.
  @param system The enumeration of the system that was profiled.
  @return A container of FunctionProfiles.
  */
  /**************************************************************************/
  Time::FunctionProfileContainer & Profiler::SystemTimes(Systems::Enumerated system)
  {
    return SystemProfiles.at(system).Time();
  }

  /**************************************************************************/
  /*!
  @brief Calculates the engine's current FPS.
  @param dt The delta time.
  */
  /**************************************************************************/
  float localCounter = 0;
  int frameCounter = 0;

  void Profiler::CalculateFPS(float dt)
  {
    localCounter += dt;
    ++frameCounter;
    if (localCounter > 0.5)
    {
      CurrentFPS = (frameCounter / localCounter);
      localCounter = 0;
      frameCounter = 0;
    }
  }

  /*=======================
     FunctionCategoryTimer
  ========================*/

  /**************************************************************************/
  /*!
  @brief SystemTimer constructor.
  @param systemName The name of the system.
  */
  /**************************************************************************/
  FunctionCategoryTimer::FunctionCategoryTimer(std::string name, std::string category) 
    : Name(name), Category(category)
  {
  }

  /**************************************************************************/
  /*!
  @brief SystemTimer destructor.
  */
  /**************************************************************************/
  FunctionCategoryTimer::~FunctionCategoryTimer()
  {
    Record();
    Report();
  }

  /**************************************************************************/
  /*!
  @brief Reports the system time to the profiler.
  */
  /**************************************************************************/
  void FunctionCategoryTimer::Report()
  {
    Engine::Profiler().Add(Time::FunctionProfile(Name, ElapsedTime), Category);
  }

  /*====================
    SYSTEM METHOD TIMER
  ====================*/
  /**************************************************************************/
  /*!
  @brief SystemMethodTimer constructor.
  @param methodName The name of the method.
  @param system The system to which this method belongs to.
  */
  /**************************************************************************/
  SystemMethodTimer::SystemMethodTimer(std::string methodName, Systems::Enumerated system)
    : MethodName(methodName), System(system)
  {
  }

  /**************************************************************************/
  /*!
  @brief SystemMethodTimer destructor.
  */
  /**************************************************************************/
  SystemMethodTimer::~SystemMethodTimer()
  {
    Record();
    Report();
  }

  /**************************************************************************/
  /*!
  @brief Reports the system time to the profiler.
  */
  /**************************************************************************/
  void SystemMethodTimer::Report()
  {
    Engine::Profiler().Add(Time::FunctionProfile(MethodName, ElapsedTime), this->System);
  }
}
