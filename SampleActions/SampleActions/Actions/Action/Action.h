#pragma once

//----------------------------------------------------------------------------/
#include <iostream> 
#include <string>
#include <vector>
//----------------------------------------------------------------------------/
// Custom types
#include "Types.h"

/**************************************************************************/
/*!
@class Action is the base class from which all other actions derive from.
*/
/**************************************************************************/
class Action {
public:
  Action(std::string type = "Action");
  ~Action();
  virtual float Update(float dt) = 0;
  bool Finished() { return IsFinished; }
  void Pause() { Paused = !Paused; }
  bool IsPaused() { return Paused; }

  static bool Trace;
  static unsigned Created;
  static unsigned Destroyed;
  std::string Type;

  using Ptr = Action*;
  using Container = std::vector<Ptr>;

protected:
  float Elapsed = 0.0f;
  float Duration = 0.0f;
  bool IsFinished = false; // When finished, the action will be removed.    
  bool Paused = false;

private:
  unsigned ID;
};
//----------------------------------------------------------------------------/