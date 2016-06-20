#pragma once
#include "..\SystemReference.h"

// Implementation class
#include "GraphicsGL.h"
// Container of graphical components for each Space
#include "../../Components/GraphicsSpace.h"

  namespace Systems {

    class Graphics : public System {
      static Graphics* Instance;
      GraphicsGL Interface;
      std::vector<Components::GraphicsSpace*> GraphicsSpaces;

    public:
      Graphics();
      void Initialize();
      void Terminate();
      void StartFrame();
      void Update(float dt);
      void EndFrame();

      // Normally you wouldn't set the singleton instance this way... I am only
      // doing it this way since we don't have an engine class that owns this system 
      // at the moment.
      static void setInstance(Graphics* inst) { Instance = inst; }
      static Graphics* getInstance() { return Instance; }

      // When a GraphicsSpace is initialized, it registers itself to the Graphics System!      
      void Register(Components::GraphicsSpace* space);

    };

  }

