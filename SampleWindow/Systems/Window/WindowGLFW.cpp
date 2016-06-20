#include "WindowGLFW.h"

// References
// http://learnopengl.com/#!Getting-started/Hello-Window

  namespace Systems {

    // Initialize the static member
    WindowGLFW* WindowGLFW::Instance = nullptr;

    bool WindowGLFW::Initialize()
    {
      if (!glfwInit())
        return false;

      // Sets some configurations before the next call to glfwCreateWindow()
      glfwWindowHint(GLFW_SAMPLES, 4); // Anti-aliasing
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS compatability
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Modern OpenGL
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

      // Create the window, passing in desired settings
      Context = glfwCreateWindow(Settings.ScreenWidth, Settings.ScreenHeight,
        Settings.Caption.c_str(), nullptr, nullptr);



      if (!Context)
        return false;
            
      // Set it as the current context
      glfwMakeContextCurrent(Context);      
      // Save a reference to this object for statics.
      Instance = this;
      // Set the input callbacks
      glfwSetKeyCallback(Context, PollKeyCallback);
      glfwSetMouseButtonCallback(Context, PollMouseButtonCallback);

      // The system was initialize successfully
      return true;
    }

    void WindowGLFW::Terminate()
    {
      
      glfwTerminate();
    }

    void WindowGLFW::StartFrame()
    {
      // Swaps the color buffer (A large buffer that contains color values for
      // each pixel in the GLFW's window) that has been used to draw in during
      // this iteration and show it as output to the screen.
      glfwSwapBuffers(Context);      
    }

    void WindowGLFW::EndFrame()
    {
    }

    void WindowGLFW::PollEvents()
    {
      // The function checks at the start of each loop iteration if GLFW has
      // been instructed to close, and if so the function returns true
      if (glfwWindowShouldClose(Context))
        Settings.OnClose();

      // Checks if any events are triggered (like keyboard input or mouse movement)
      // and calls the corresponding functions (which we can set via callback methods)
      // We usually call eventprocessing functions at the start of a loop iteration
      glfwPollEvents();
    }
  

    /* The key input function takes a GLFWwindow as its first argument, an integer that 
       specifies the key pressed, an action that specifies if the key is pressed or released 
       and an integer representing some bit flags to tell you if shift, control, alt or super
       keys have been pressed. Whenever a user pressed a key, GLFW calls this function and 
       fills in the proper arguments for you to process. */
    void WindowGLFW::PollKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
    {
      if (action == GLFW_PRESS) {
        Instance->PollKeyPressed(key);
      }
      else if (action == GLFW_RELEASE) {
        Instance->PollKeyReleased(key);
      }
    }

    void WindowGLFW::PollMouseButtonCallback(GLFWwindow * window, int button, int action, int mode)
    {
      if (action == GLFW_PRESS) {
        Buttons buttonPressed;
        switch (button) {
        case GLFW_MOUSE_BUTTON_1:
          buttonPressed = Buttons::Left;
          break;
        }

        Instance->DispatchMouseDown(buttonPressed);
      }
    }

    void WindowGLFW::PollKeyPressed(int keyPressed)
    {
      Keys key = Keys::Null;

      switch (keyPressed) {
      case GLFW_KEY_ESCAPE:
        key = Keys::Escape;
        std::cout << "'Escape' key pressed! \n";        
        break;
      case GLFW_KEY_A:
        key = Keys::A;
        std::cout << "'A' key pressed! \n";
        break;
      default:
        break;
      }

      if (key != Keys::Null)
        DispatchKeyDown(key);

    }

    void WindowGLFW::PollKeyReleased(int keyReleased)
    {
      Keys key;

      switch (keyReleased) {
      case GLFW_KEY_ESCAPE:
        key = Keys::Escape;
        std::cout << "'Escape' key released! \n";
        break;
      case GLFW_KEY_A:
        key = Keys::A;
        std::cout << "'A' key released! \n";
        break;
      default:
        break;
      }
    }


  }
