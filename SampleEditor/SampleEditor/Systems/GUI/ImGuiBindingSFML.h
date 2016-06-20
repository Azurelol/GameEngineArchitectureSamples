#pragma once

#include "ImGuiBinding.h"
#include "../Window/WindowSFML.h"

namespace Systems {

  class ImGuiBindingSFML : public ImGuiBinding {  

    sf::Clock TimeElapsed; // The time elapsed

  public:
    void PollEvents();
    void UpdateTimeStep();
    void UpdateInput();
    bool BindInput();
    void RenderDrawLists();

  };

}
