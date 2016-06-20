/*****************************************************************************/
/*!
@file   Profiler.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/25/2016
*/
/******************************************************************************/
#pragma once
#include "Timer.h"
#include "Systems.h"
  
namespace SPEngine
{
/**************************************************************************/
/*!
@class SystemTimer An object that times a system's method.
*/
/**************************************************************************/
  class SystemMethodTimer : public Time::FunctionTimer {
  public:
    SystemMethodTimer(std::string methodName, Systems::Enumerated system);
    ~SystemMethodTimer();
    virtual void Report();
  private:
    const std::string MethodName;
    Systems::Enumerated System;
  };


  /**************************************************************************/
  /*!
  @class FunctionTimer An object that times a function of a specified
         category.
  */
  /**************************************************************************/
  class FunctionCategoryTimer : public Time::FunctionTimer {
  public:
    FunctionCategoryTimer(std::string name, std::string category);
    ~FunctionCategoryTimer();
    virtual void Report();
  private:
    const std::string Name;
    const std::string Category;
  };

  /**************************************************************************/
  /*!
  @class Profiler Runs various diagnostics on the engine and stores that
         data.
  @todo  Decide whether to use a branching Add method and enums for different
         types or different methods like being done currently.
  */
  /**************************************************************************/
  class Profiler {
  public:
    void Add(Time::FunctionProfile profile, std::string category);
    void Add(Time::FunctionProfile systemTime, Systems::Enumerated system) ;
    float FPS();
    void Update(float dt);
    Time::FunctionProfileContainer& Times(std::string category);
    Time::FunctionProfileContainer& SystemTimes(Systems::Enumerated system);

  private:

    // Stores the current FPS
    float CurrentFPS;    
    // Default map for Profiles
    Time::FunctionProfileMap Profiles;
    // Custom map for Profiles using strongly-typed enumerations!
    using SystemProfileMap = std::map<Systems::Enumerated, Time::FunctionProfileTimes>;
    SystemProfileMap SystemProfiles;

    // Methods
    void AddSystemTime(Time::FunctionProfileContainer& container, Time::FunctionProfile& time);
    void CalculateFPS(float dt);
    void Clear();
  };


}