#pragma once

// GLEW
#define GLEW_STATIC
#include <GLEW\glew.h>
// Shaders
#include "../../Resources/Shader.h"

  namespace Systems {

    class GraphicsGL {

      void CompileShaders();

    public:
      GraphicsGL();
      void Initialize();
      void Terminate();
      void StartFrame();
      void EndFrame();
      static GLenum ErrorCheck(std::string message);

    };

  }
