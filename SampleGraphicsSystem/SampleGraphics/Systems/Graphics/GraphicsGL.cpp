#include "GraphicsGL.h"

#include "../../Objects/Utilities.h"
#include "../../Components/GraphicalInclude.h"

  namespace Systems {

    GraphicsGL::GraphicsGL()
    {
    }

    void GraphicsGL::Initialize()
    {
      Trace("Initializing GLEW");
      // GLEW manages function pointers for OpenGL, so we want to initialize
      // it before calling any OpenGL functions. Setting glewExperimental to
      // true uses more modern techniques for managing OpenGL functionality.
      glewExperimental = GL_TRUE;
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_MULTISAMPLE);

      // If OpenGL failed to initialize...
      if (glewInit() != GLEW_OK) {
        Trace("Failed to initialize GLEW");
      }

      printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));

      CompileShaders();
    }

    void GraphicsGL::Terminate()
    {
    }

    void GraphicsGL::StartFrame()
    {
      // Clear the colorbuffer. It wouldn't be a bad idea for the clearcolor
      // to be a Vec4 member which can be modified/accessed at any time.
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
    }

    void GraphicsGL::EndFrame()
    {
    }

    GLenum GraphicsGL::ErrorCheck(std::string message)
    {
      GLenum error;
      error = glGetError();
      if (error) {
        Trace(message);
      }
      return error;
    }

    void GraphicsGL::CompileShaders()
    {
      Trace("Now compiling shaders for all graphical components...");
      Components::Sprite::Configure();
    }

  }
