/*****************************************************************************/
/*!
\file   Driver.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/27/2016
\brief  Driver for the Sample Window project.
*/
/******************************************************************************/

// Window System
#include "Systems\Window\Window.h"
// A scope-based timer that we use to precisely set how much each "frame" should take
#include "Timer.h"

// A boolean that keeps the main loop running and a provided callback function
// to turn it off!
bool Active;
void Shutdown() { Active = false; }

// A function of the specified signature that we will be subscribing to the window system.
// When input is detected by it, it will call this function.
// The signature is specified by the alias "KeyDownCallback"
void OnKeyDown(Keys key) {
  switch (key) {
  case Keys::A:
    printf("A was pressed! \n");
    break;
  case Keys::Escape:
    printf("Escape was pressed! \n");
    break;
  default:
    break;
  }

}

int main(int argc, char *argv[]) {

  //--------------------------------------------------------------------------/
  // This is a variation of the "Builder" pattern:
  Systems::WindowSettings windowSettings;
  // What API to use (change the enum and try it yourself gyahaha)
  windowSettings.Interface = Systems::WindowSettings::API::SFML;
  // What function to call when the window is closed
  windowSettings.OnClose = &Shutdown;
  // Instantiate the window system
  auto windowSystem = std::shared_ptr<Systems::Window>(new Systems::Window(windowSettings));
  // Set the static pointer for it 
  Systems::Window::setInstance(windowSystem.get());
  //--------------------------------------------------------------------------/
  // Initialize the system
  windowSystem->Initialize();
  //--------------------------------------------------------------------------/
  // Subscribe our callback functions to it so we can be notified of input
  windowSystem->Subscribe(&OnKeyDown);
  //--------------------------------------------------------------------------/
  // Main loop
  Active = true;
  float dt = 1.0f / 60.0f;
  auto width = windowSystem->getSettings().ScreenWidth;
  auto height = windowSystem->getSettings().ScreenHeight;
  while (Active) {
    Time::ScopeTimer frameTimer(&dt);
    windowSystem->StartFrame();
    // OpenGL updating --------------
    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // ------------------------------
    windowSystem->Update(dt);
    windowSystem->EndFrame();
  }
  //--------------------------------------------------------------------------/
  return 0;
}