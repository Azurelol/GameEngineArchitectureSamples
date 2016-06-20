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

// STL Libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

namespace Debug {

  class Tracer {
    std::stringstream Stream;
    std::ofstream File;

  public:
    Tracer(std::string fileName);
    ~Tracer();
    template<typename T>
    Tracer& operator<<(const T& data) {
      #ifndef _PRODUCTION
      std::cout << data;
      File << data;
      Stream << data;
      return *this;
      #else
      return *this;
      #endif

    }

  };

  // Singleton trace object
  extern std::unique_ptr<Tracer> TraceObj;
  // Main trace macro
  #define Trace (*::Debug::TraceObj)  


}