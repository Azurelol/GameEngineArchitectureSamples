#pragma once
#include "WindowSettings.h"

namespace Systems {

  class WindowInterface {
  protected:
    WindowSettings& Settings;

  public:
    //----------------------------------------------------------------------/
    // A function called when the window is polling for OS-specific window events
    using PollEventCallback = std::function<void(void)>;
    // A function called when the window system detects a specific manner of input
    using KeyDownCallback = std::function<void(Keys)>;
    using MouseDownCallback = std::function<void(Buttons)>;
    //----------------------------------------------------------------------/
    WindowInterface(WindowSettings& settings) : Settings(settings) {}
    virtual bool Initialize() = 0;
    virtual void Terminate() = 0;
    virtual void StartFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void PollEvents() = 0;
    //----------------------------------------------------------------------/
    // Provide a way to subscribe functions to be called
    void Subscribe(KeyDownCallback callback) 
    {
      KeyDownSubscribers.push_back(callback);
    }
    void Subscribe(MouseDownCallback callback) 
    {
      MouseDownSubscribers.push_back(callback);
    }
    void Subscribe(PollEventCallback callback) 
    {
      PollEventSubscribers.push_back(callback);
    }
    // It would be a good idea to provide a way to unsubscribe as well!
    // (Such as when the function is an object that is about to be destroyed)

  protected:
    std::vector<KeyDownCallback> KeyDownSubscribers;
    std::vector<MouseDownCallback> MouseDownSubscribers;
    std::vector<PollEventCallback> PollEventSubscribers;
    //----------------------------------------------------------------------/
    // This will inform every subscriber
    void DispatchKeyDown(Keys key) 
    {
      for (auto& callback : KeyDownSubscribers)
        callback(key);
    }

    void DispatchMouseDown(Buttons button)
    {
      for (auto& callback : MouseDownSubscribers)
        callback(button);
    }


  };

}