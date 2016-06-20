#include "Graphics.h"

#include "../../Objects/Space.h"
#include "../../Components/CameraViewport.h"

  namespace Systems {

    Graphics* Graphics::Instance = nullptr;

    /**************************************************************************/
    /*!
    @brief Default constructor for the Graphics System.
    */
    /**************************************************************************/
    Graphics::Graphics() : System("Graphics")
    {
    }

    /**************************************************************************/
    /*!
    @brief Initializes the Graphics system.
    */
    /**************************************************************************/
    void Graphics::Initialize()
    {
      Interface.Initialize();
    }

    /**************************************************************************/
    /*!
    @brief Terminates the Graphics System.
    */
    /**************************************************************************/
    void Graphics::Terminate()
    {
      Interface.Terminate();
    }

    /**************************************************************************/
    /*!
    @brief Starts the current frame.
    */
    /**************************************************************************/
    void Graphics::StartFrame()
    {
      Interface.StartFrame();
    }

    /**************************************************************************/
    /*!
    @brief Updates the graphics system, rendering each graphical object..
    @param The delta time.
    @note  The projection/view uniforms are set once for each shader,
           while the others change depending on the object.
    */
    /**************************************************************************/
    void Graphics::Update(float dt)
    {
      // For every GraphicsSpace component that has been registered..
      for (auto& graphicsSpace : GraphicsSpaces) {

        // Get its space
        auto space = graphicsSpace->getSpace();
        // Get its default camera
        auto camera = space->getComponent<Components::CameraViewport>()->getDefaultCamera();
        // If no camera has been set, do nothing
        if (!camera)
          continue;

        auto& graphicalComponents = graphicsSpace->getGraphicalComponents();
        // For every graphical component...
        for (auto& graphical : graphicalComponents) {
          // If not visible, don't draw it!
          if (!graphical->getVisible())
            continue;

          graphical->SetUniforms(camera);
          graphical->Draw();
        }        
      }
    }


    /**************************************************************************/
    /*!
    @brief Ends the current frame.
    */
    /**************************************************************************/
    void Graphics::EndFrame()
    {
      Interface.EndFrame();
    }

    void Graphics::Register(Components::GraphicsSpace * space)
    {
      TraceObject(space->Owner()->getName() + " has registered!");
      GraphicsSpaces.push_back(space);
    }

  }
