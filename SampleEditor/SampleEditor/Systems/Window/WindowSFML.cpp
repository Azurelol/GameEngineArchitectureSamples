#include "WindowSFML.h"

  namespace Systems {

    // Initialize the static member
    WindowSFML* WindowSFML::Instance = nullptr;

    WindowSFML::WindowSFML(WindowSettings & settings) : WindowInterface(settings)
    {
      Instance = this;
    }

    WindowSFML::~WindowSFML()
    {
      Instance = nullptr;
    }

    bool WindowSFML::Initialize()
    {
      // First, set the settings
      SetContextSettings();
      
      //------------------------------
      // Create the context object
      Context.reset(new sf::Window(sf::VideoMode(Settings.ScreenWidth, Settings.ScreenHeight), 
        Settings.Caption, 
        sf::Style::Default, 
        ContextSettings));
      // Set vertical synchronization, handled automatically by the GPU.
      Context->setVerticalSyncEnabled(true);
      // Implemented by SFML itself using a high-resolution clock to set a specific framerate
      // Can be unreliable at high framerates. Do not use alongside vsync.
      //Context->setFramerateLimit(60);
      //------------------------------

      // No context being created will end up to the engine terminating early...
      if (!Context)
        return false;

      return true;
    }
    
    void WindowSFML::SetContextSettings()
    {
      // Stores the settings for the underlying SFML window context
      ContextSettings.depthBits = 24;
      ContextSettings.stencilBits = 8;
      ContextSettings.antialiasingLevel = 4;
      ContextSettings.majorVersion = 3;
      ContextSettings.minorVersion = 3;
    }

    void WindowSFML::PollEvents(const PollEventCallbackContainer& callbacks)
    {
      // Check all of the event types that have been triggered since the last
      // iteration of the loop. This needs to be called in a loop for all
      // events to process since its an event 'queue':
      while (Context->pollEvent(CurrentEvent)) {

        // Close
        if (CurrentEvent.type == sf::Event::Closed)
          Settings.OnClose();        

        PollInput();

        // Call every function that has subscribed to be notified when
        // this system is polling for events
        for (auto& callback : callbacks) {
          callback();
        }
      }

    }

    void WindowSFML::PollInput()
    {
      switch (CurrentEvent.type) {
      case sf::Event::KeyPressed:
        PollKeyPressed();
        break;
      case sf::Event::MouseButtonPressed:
        PollMouseButtonPressed();
        break;
      default:
        break;
        // And many others..
      }
    }

    void WindowSFML::PollKeyPressed()
    {
      Keys key;

      // To find out what key was pressed...
      switch (CurrentEvent.key.code) {
      case sf::Keyboard::Escape:
        key = Keys::Escape;
        std::cout << "'Escape' key pressed! \n";
        break;
      case sf::Keyboard::A:
        key = Keys::A;
        std::cout << "'A' key pressed! \n";
        break;
      }
    }

    void WindowSFML::PollMouseButtonPressed()
    {
      // The mouse position at the time it was pressed...
      auto mousePosX = CurrentEvent.mouseButton.x;
      auto mousePosY = CurrentEvent.mouseButton.y;

      // To find out what button was pressed...
      Buttons button;

      switch (CurrentEvent.mouseButton.button) {
      case sf::Mouse::Button::Left:
        button = Buttons::Left;
        std::cout << "'Left' button pressed! \n";
        break;

      }

    }

    void WindowSFML::StartFrame()
    {
    }

    void WindowSFML::EndFrame()
    {
      Context->display();
    }

    void WindowSFML::Terminate()
    {
      Context->close();
    }

  }
