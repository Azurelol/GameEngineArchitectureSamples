/******************************************************************************/
/*!
@file   Trace.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/22/2016
@brief  A simple trace object that redirects output to stdio and a specified file
in its constructor.
*/
/******************************************************************************/
#pragma once

#include <iostream>

namespace Debug {

  // Simple trace
#define Trace(message) std::cout << message << "\n";
  // Quick trace, just providing the function name.
#define TraceF(message) std::cout << __FUNCTION__  << ": " << message << "\n";
  // Verbose trace, with the name of the object's name prefixed. It is up to you how
  // you want to decorate this.
#define TraceObject(message) std::cout << "[" << Name << "] " << __FUNCTION__ << ": " << message << "\n"

}