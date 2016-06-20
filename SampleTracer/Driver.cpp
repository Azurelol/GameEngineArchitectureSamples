/*****************************************************************************/
/*!
\file   Driver.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  Driver for the Sample Zilch Engine project.
*/
/******************************************************************************/
// Packages
#include "Trace.h"


void TestTrace() {
  Trace << "This is the base trace macro that uses the stream operator. \n";
}

/*============================================
   Some examples of Trace macros you can write
=============================================*/
//----------------------------------------------------------------------------/
// Traces using the function name as a prefix
#define TraceFunction(message) Trace << __FUNCTION__ << ": " << message << "\n"

void TestTraceFunction() {
  TraceFunction("I am tracing this function!");
}

//----------------------------------------------------------------------------/
// Now let's get "clever" regarding tracing. If for example we made every class
// that we use in our engine derive from a single base class that has a string identifier
// for the name of the object, we could do something like this!
class Object {
public:
  std::string Name;
  Object(const std::string& name) : Name(name) {}
};

// This macro will prefix the name of the object, then the function that 
// is being called before the message
#define TraceObject(message) Trace << "[" << Name << "] "<< __FUNCTION__ << ": " << message << "\n"

class DerivedObject : public Object {
public:
  DerivedObject() : Object("Coolio") {}
  void TestTraceObject() {
    TraceObject("Hello!");
  }
};
//----------------------------------------------------------------------------/


int main(void) {

  // Instantiate the trace object. It will create the file with the specified
  // name and start redirectering output to it and stdio.
  Debug::TraceObj.reset(new Debug::Tracer("Log.txt"));
  // A simple trace, taking any string
  TestTrace();
  // A trace that prefixes the function name
  TestTraceFunction();
  // A trace that prefix the name of the object and the function name as well
  auto object = DerivedObject();
  object.TestTraceObject();

  return 0;

}