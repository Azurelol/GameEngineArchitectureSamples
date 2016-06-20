#pragma once
#include "../SystemReference.h"

// Settings
#include "WindowSettings.h"
// Implementation
#include "WindowSFML.h"

namespace Systems {

  class Window : public System {

    static Window* Instance;

  public:
    //----------------------------------------------------------------------------/
    WindowSettings Settings; // Can hold the settings in here or pass them by reference,
                             // having the engine itself "hold" them.
    // Change the API by assigning a different class type:
    using ImplementationAPI = WindowSFML;
    ImplementationAPI Implementation;
    //----------------------------------------------------------------------------/

    Window(WindowSettings settings);
    void Initialize();
    void Terminate();
    void StartFrame();
    void Update(float dt);
    void EndFrame();

    // Normally you wouldn't set the singleton instance this way... I am only
    // doing it this way since we don't have an engine class that owns this system 
    // at the moment.
    static void setInstance(Window* inst) { Instance = inst; }
    static Window* getInstance() { return Instance; }
    static const Vec2& Resolution();


  };

}
