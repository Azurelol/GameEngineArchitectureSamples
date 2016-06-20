/*****************************************************************************/
/*!
\file   Driver.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   6/6/2016
\brief  Driver for the Sample Editor project.
*/
/******************************************************************************/
// GUI: dear imgui
// https://github.com/ocornut/imgui

// It has to included in this order or the following happens:
// http://stackoverflow.com/questions/8580675/error-gl-h-included-before-glew-h
#include "Systems\GUI\GUI.h"
#include "Systems\Window\Window.h"
#include "Utilities.h"

// Provided bool and callback function to turn off the main loop
bool Active;
void Shutdown() { Active = false; }

// The editor class example --------------------------------------------------/
class Editor : public System {

public:
  
  void Initialize() {

  }

  void Update(float dt) {
    static bool show = true;
    ImGui::ShowTestWindow(&show);
  }

  void Terminate() {

  }

};
//----------------------------------------------------------------------------/
int main(void) {
  
  Trace("Sample Editor Demonstration, using modern OpenGL and dear imgui");
  //--------------------------------------------------------------------------/
  // This is a variation of the "Builder" pattern:
  // https://en.wikipedia.org/wiki/Builder_pattern
  Systems::WindowSettings windowSettings;
  windowSettings.Interface = Systems::WindowSettings::API::SFML;
  // The function that will be called when the window is closed
  windowSettings.OnClose = &Shutdown; 
  // Instantiate the window system
  auto windowSystem = std::shared_ptr<Systems::Window>(new Systems::Window(windowSettings));
  // Set the static pointer for it 
  Systems::Window::setInstance(windowSystem.get());
  // Instantiate the gui system
  auto guiSystem = std::shared_ptr<Systems::GUI>(new Systems::GUI());
  // Instantiate the editor system
  auto editor = std::shared_ptr<Editor>(new Editor());
  //--------------------------------------------------------------------------/
  // Initialize the window system
  windowSystem->Initialize();
  //--------------------------------------------------------------------------/
  // We have to initialize the OpenGL context before the GUI. Normally this would be
  // done by the graphics system. Since we don't have one we will do it here instead.
  Trace("Initializing GLEW");
  // GLEW manages function pointers for OpenGL, so we want to initialize
  // it before calling any OpenGL functions. Setting glewExperimental to
  // true uses more modern techniques for managing OpenGL functionality.
  glewExperimental = GL_TRUE;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // If OpenGL failed to initialize...
  if (glewInit() != GLEW_OK) {
    Trace("Failed to initialize GLEW: " + glGetError());
    return -1;
  }
  //--------------------------------------------------------------------------/
  // Initialize the GUI systen next, then Editor
  guiSystem->Initialize();
  editor->Initialize();
  //--------------------------------------------------------------------------/
  // Main loop
  Active = true;
  float dt = 1.0f / 60.0f;
  auto width = windowSystem->getSettings().ScreenWidth;
  auto height = windowSystem->getSettings().ScreenHeight;
  while (Active) {
    Time::ScopeTimer frameTimer(&dt);
    windowSystem->StartFrame();
    guiSystem->StartFrame();
    // OpenGL updating --------------
    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // ------------------------------
    windowSystem->Update(dt);
    editor->Update(dt);
    guiSystem->EndFrame();
    windowSystem->EndFrame();
  }
  //--------------------------------------------------------------------------/

  return 0;
}