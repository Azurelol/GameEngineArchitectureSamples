/******************************************************************************/
/*!
@file   Trace.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/22/2016
@brief  A simple trace object that redirects output to stdio and a specified file
        in its constructor.
*/
/******************************************************************************/
#include "Trace.h"

namespace Debug {

  std::unique_ptr<Tracer> TraceObj;

  /**************************************************************************/
  /*!
  @brief Tracer constructor.
  @param fileName The name of the file to write to.
  */
  /**************************************************************************/
  Tracer::Tracer(std::string fileName)
  {
    File.open(fileName, std::ios::trunc);
    File.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    if (!File)
      std::cerr << "Could not open '" << fileName << "' for writing!" << std::endl;
    std::cout << "Now tracing to '" << fileName << "'" << std::endl;
  }

  /**************************************************************************/
  /*!
  @brief Tracer destructor.
  @param fileName The name of the file to write to.
  */
  /**************************************************************************/
  Tracer::~Tracer()
  {
    File.close();
  }

}