/******************************************************************************/
/*!
@file   Main.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   5/16/2016
@brief  The entry point for the engine.
*/
/******************************************************************************/
#include "Core\Engine\Engine.h"

// Engine singleton
extern std::unique_ptr<SPEngine::Engine> SampleEngine;

int main(int argc, char* argv[]) {

  // Create the engine object
  SPEngine::SampleEngine.reset(new SPEngine::Engine());

  // We enclose the whole engine's operation inside a try-catch block
  // in order to catch exceptions we may decide to throw.
  try {
    // Initialize it
    SPEngine::SampleEngine->Initialize();
    // Start its main loop (which will keep... looping until an exit condition is met)
    SPEngine::SampleEngine->Loop();
  }

  // Define your own exception here instead
  catch (...) {
    // Define what to do here; usually printing the exception to console or a window
    std::cout << "Oh no the engine has crashed!" << std::endl;
    return 1;
  }

  // Close the engine, clean up
  SPEngine::SampleEngine->Terminate();

  return 0;
}

// It is not a bad idea to provide several entry points to 'main'
int WinMain(int argc, char* argv[]) {
  return main(argc, argv);
}