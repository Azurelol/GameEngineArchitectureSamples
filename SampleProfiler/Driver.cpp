/*****************************************************************************/
/*!
\file   Driver.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/27/2016
\brief  Driver for the Sample Profiler project.
*/
/******************************************************************************/
// Packages
#include "Engine.h"

// Sample test battery
static std::string testCategory = "Samples";
void Test1_EmptyFunction();
void Test2_SmallFunction();
void Test3_MediumFunction();
void Test4_LargeFunction();

// Engine singleton
extern std::unique_ptr<SPEngine::Engine> SampleEngine;

int main(void) {

  // Create the engine object.
  SPEngine::SampleEngine.reset(new SPEngine::Engine());
  SPEngine::SampleEngine->Initialize();

  // Grab a reference to the profiler
  auto& profiler = SPEngine::Engine::Profiler();

  //---------------------------------------------------------------------------/
  // SET 1: Run some sample functions and profile, categorizing with strings
  std::cout << "SET 1: Run some sample functions and profile, categorizing with strings!" << std::endl;
  Test1_EmptyFunction();
  Test2_SmallFunction();
  Test3_MediumFunction();
  Test2_SmallFunction();
  Test4_LargeFunction();  
  // Retrieve the profiles for the functions of the specified category
  auto& samples = profiler.Times(testCategory);
  for (auto& sample : samples) {
    sample.Print();
  } 
  std::cout << std::endl;
  //---------------------------------------------------------------------------/
  // SET 2: Update the engine's systems and profile using strongly-typed enum categories
  std::cout << "SET 2: Update the engine's systems and profile using strongly-typed enum categories!" << std::endl;
  // Manually update the engine. Normally this would be inside a loop construct...
  for (unsigned i = 0; i < 500; ++i) {
    SPEngine::SampleEngine->Update(SPEngine::Engine::Dt());
  }
  // Retrieve the profiles for the physics system functions
  auto& physicsTimes = profiler.SystemTimes(SPEngine::Systems::Enumerated::Physics);
  for (auto& profile : physicsTimes) {
    profile.Print();
  }
  // Retrieve the profiles for the graphics system functions
  auto& graphicsTimes = profiler.SystemTimes(SPEngine::Systems::Enumerated::Graphics);
  for (auto& profile : graphicsTimes) {
    profile.Print();
  }
  //---------------------------------------------------------------------------/

  return 0;
}

void Test1_EmptyFunction() {
  SPEngine::FunctionCategoryTimer(__FUNCTION__, testCategory);
}


void Test2_SmallFunction()
{
  SPEngine::FunctionCategoryTimer(__FUNCTION__, testCategory);
  // O(N)
  for (unsigned i = 0; i < 500; ++i) {
    unsigned j = i + i + i;
  }
}

void Test3_MediumFunction()
{
  SPEngine::FunctionCategoryTimer(__FUNCTION__, testCategory);
  // O(N^2)
  for (unsigned i = 0; i < 500; ++i) {
    for (unsigned j = 0; j < 500; ++j) {
      unsigned k = j + j + i + i;
    }
  }
}

void Test4_LargeFunction()
{
  SPEngine::FunctionCategoryTimer(__FUNCTION__, testCategory);
  // O(N^2)
  for (unsigned i = 0; i < 500; ++i) {
    for (unsigned j = 0; j < 500; ++j) {
      for (unsigned k = 0; k < 500; ++k) {
        unsigned a = k * k * j + j + i + i;
      }
    }
  }

}
