#pragma once

#define GLEW_STATIC
#include <GLEW\glew.h>
#include <GLM\glm.hpp>

// Don't forget to include 'imgui.cpp, imgui_demo.cpp,  imgui_draw.cpp' 
// somewhere in the project.
#include <DEARIMGUI\imgui.h>

namespace Systems {

  struct OpenGLStateData {
    GLint lastProgram;
    GLint lastTexture;
    GLint lastArrayBuffer;
    GLint lastElementArrayBuffer;
    GLint lastVertexArray;
    GLint lastBlendSrc;
    GLint lastBlendDst;
    GLint lastBlendEquationRGB;
    GLint lastBlendEquationAlpha;
    GLint lastViewport[4];
    GLboolean lastEnableBlend;
    GLboolean lastEnableCullFace;
    GLboolean lastEnableDepthTest;
    GLboolean lastEnableScissorTest;
  };

  class ImGuiBinding {
        
  protected:
    double       Time = 0.0f;
    bool         MousePressed[3] = { false, false, false };
    float        MouseWheel = 0.0f;
    GLuint       FontTexture = 0;
    int          ShaderHandle = 0, VertHandle = 0, FragHandle = 0;
    int          AttribLocationTex = 0, AttribLocationProjMtx = 0;
    int          AttribLocationPosition = 0, AttribLocationUV = 0, AttribLocationColor = 0;
    unsigned int VboHandle = 0, VaoHandle = 0, ElementsHandle = 0;

  public:
    void Initialize();
    void Terminate();
    void StartFrame();
    void EndFrame();
    bool CreateDeviceObjects();
    bool IsCapturingMouse();
    bool IsCapturingKeyboard();
    OpenGLStateData BackupGLState();
    void RestoreGLState(const OpenGLStateData& currentState);
    //------------------------------------------------------------------------/
    virtual bool BindRendering();
    // Still not sure on whether this method changes depending on API
    virtual void RenderDrawLists(); 
    //------------------------------------------------------------------------/
    // These have to be implemented by API-specific bindings
    virtual void PollEvents() = 0;
    virtual bool BindInput() = 0;
    virtual void UpdateDisplaySize();
    virtual void UpdateTimeStep() = 0;
    virtual void UpdateInput() = 0;
    //------------------------------------------------------------------------/

  };



}
