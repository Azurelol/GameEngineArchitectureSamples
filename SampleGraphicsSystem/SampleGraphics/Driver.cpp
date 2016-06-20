/*****************************************************************************/
/*!
\file   Driver.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/27/2016
\brief  Driver for the Sample Window project.
*/
/******************************************************************************/

// Window, Graphics systems
#include "Systems\SystemsInclude.h"
// Space
#include "Objects\Space.h"
#include "Components\GraphicsSpace.h"
#include "Components\CameraViewport.h"
// GameObjects
#include "Components\Camera.h"
#include "Components\Transform.h"
#include "Components\Sprite.h"

int main(void) {

  //--------------------------------------------------------------------------/
  Trace("1. First, let's instantiate the Window and Graphics systems.");
  // Let's instantiate the Window and Graphics Systems. Normally this would be
  // the job of an "engine" class which also would own a collection of them.
  Systems::WindowSettings windowSettings;
  windowSettings.Caption = "Sample Graphics Demonstration";
  auto windowSystem = new Systems::Window(windowSettings); 
  Systems::Window::setInstance(windowSystem); 
  auto graphicsSystem = new Systems::Graphics();  
  Systems::Graphics::setInstance(graphicsSystem);  

  //--------------------------------------------------------------------------/
  Trace("2. Let's construct the Space, and add to it the GraphicsSpace and CameraViewport components");
  auto space = new Space("DefaultSpace");
  // The GraphicsSpace is the component that keeps track of all the current graphical objects
  // in the space, that is GameObjects with graphical components on them. The GraphicsSystem
  // in turn looks over every GraphicsSpace, drawing its objects .
  space->AddComponent(new Components::GraphicsSpace(*space));
  // Let's register the GraphicsSpace. It will register itself to the GraphicsSystem.
  // This call can be done in either the constructor or the intitialize method.
  auto graphicsSpace = space->getComponent<Components::GraphicsSpace>();
  graphicsSystem->Register(graphicsSpace);
  // The CameraViewport component acts as the "eyes" onto its given space. It does so
  // by pointing to a GameObject on the space with a 'Camera' component on it.
  // We will need to wait a bit before making the "link".
  space->AddComponent(new Components::CameraViewport(*space));
  auto cameraViewport = space->getComponent<Components::CameraViewport>();

  //--------------------------------------------------------------------------/
  Trace("3. Now let's initialize the systems");
  windowSystem->Initialize();
  // Initializing the Graphics System will do the following:
  // 1. Initialize GLEW
  // 2. Compile all Shaders. For this sample there's only one shader, the one for
  //    Sprites.
  graphicsSystem->Initialize();

  //--------------------------------------------------------------------------/
  Trace("Now let's construct the Camera object for the scene, adding the Transform and Camera components");
  auto cameraObj = new GameObject("Camera", *space);
  // The transform component represents the object as residing on that space
  cameraObj->AddComponent(new Components::Transform(*cameraObj));
  cameraObj->AddComponent(new Components::Camera(*cameraObj));
  auto cameraObjTransform = cameraObj->getComponent<Components::Transform>();
  auto cameraObjCamera = cameraObj->getComponent<Components::Camera>();
  // Add this GameObject to the space
  space->ActiveGameObjects.push_back(cameraObj);
  // In addition, let's set this object's camera as the default camera for the space's
  // 'CameraViewport' component
  cameraViewport->setDefaultCamera(cameraObjCamera);
  // Let's place the camera in front of the Sprite object, at (0,0,1). Remember
  // that the camera will be looking in the -z direction by default
  cameraObjTransform->setTranslation(Vec3(0.0f, 0.0f, 1.0f));

  //--------------------------------------------------------------------------/
  Trace("Let's construct a GameObject to act as the Sprite, adding the Transform and Sprite components");
  auto spriteObj = new GameObject("Sunshine", *space);
  spriteObj->AddComponent(new Components::Transform(*spriteObj));
  spriteObj->AddComponent(new Components::Sprite(*spriteObj));
  auto spriteObjTransform = spriteObj->getComponent<Components::Transform>();
  auto spriteObjSprite = spriteObj->getComponent<Components::Sprite>();

  // Let's register this Sprite component onto the GraphicsSpace of its Space
  // This is normally done in the constructor for the Sprite
  spriteObjSprite->Register();
  
  // Now, let's construct the SpriteSource it will use. A SpriteSource is an
  // object encapsulating the image data. Sprites hold references to which
  // SpriteSources they use. Ideally resources like SpriteSources would be
  // managed by a resource manager. Since we don't have one we will be constructing it
  // in place.
  Trace("Now constructing the SpriteSource that will be used by this Sprite");
  auto spriteSource = new Resources::SpriteSource("Wow");
  spriteSource->setAssetPath("Assets\\doge-thrones.jpg");
  spriteSource->LoadImageFromFile();
  spriteSource->GenerateTexture();
  spriteObjSprite->setSpriteSourceHandle(spriteSource);  
  // The size of the Sprite can be modified in this way
  //spriteObjTransform->setScale(Vec3(2.0f, 2.0f, 2.0f));
  // The color of the Sprite can be modified here
  //spriteObjSprite->setColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //--------------------------------------------------------------------------/
  // Now that everything has been initialized, constructed and prepared,
  // Let's imitate a game engine's core loop by updating all systems until
  // an exit condition is met.
  Trace("Now updating the window and graphics systems");
  float deltaTime = 1.0f / 60.0f;
  while (true) {
    Time::ScopeTimer frameTimer(&deltaTime);
    windowSystem->StartFrame();
    graphicsSystem->StartFrame();
    windowSystem->Update(deltaTime);
    graphicsSystem->Update(deltaTime);
    graphicsSystem->EndFrame();
    windowSystem->EndFrame();    
  }


  // Let's clean up. Ideally this all would be done automatically with
  // smart pointers / factories / destructors, ho!
  delete space; delete graphicsSpace; delete cameraViewport;
  delete cameraObj; delete spriteObj; delete spriteSource;
  delete windowSystem; delete graphicsSystem;

  return 0;
}