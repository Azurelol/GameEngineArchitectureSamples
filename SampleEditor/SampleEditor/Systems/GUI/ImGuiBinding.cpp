#include "ImGuiBinding.h"

#include "../Window/Window.h"

namespace Systems {

  void ImGuiBinding::Initialize()
  {
    CreateDeviceObjects();
    BindInput();
    BindRendering();
  }

  void ImGuiBinding::Terminate()
  {
    if (VaoHandle) glDeleteVertexArrays(1, &VaoHandle);
    if (VboHandle) glDeleteBuffers(1, &VboHandle);
    if (ElementsHandle) glDeleteBuffers(1, &ElementsHandle);
    VaoHandle = VboHandle = ElementsHandle = 0;

    // If we compiled the shader manually..
    glDetachShader(ShaderHandle, VertHandle);
    glDeleteShader(VertHandle);
    VertHandle = 0;
    glDetachShader(ShaderHandle, FragHandle);
    glDeleteShader(FragHandle);
    FragHandle = 0;
    glDeleteProgram(ShaderHandle);
    ShaderHandle = 0;    

    if (FontTexture)
    {
      glDeleteTextures(1, &FontTexture);
      ImGui::GetIO().Fonts->TexID = 0;
      FontTexture = 0;
    }

    ImGui::Shutdown();
  }

  void ImGuiBinding::StartFrame()
  {
    UpdateDisplaySize();
    UpdateTimeStep();
    UpdateInput();
    ImGui::NewFrame();
  }

  void ImGuiBinding::EndFrame()
  {
    ImGui::Render();
    RenderDrawLists();
  }

  bool ImGuiBinding::CreateDeviceObjects()
  {
    //------------------------------------------------------------------------/
    // Compile a shader
    const GLchar *vertex_shader =
      "#version 330\n"
      "uniform mat4 ProjMtx;\n"
      "in vec2 Position;\n"
      "in vec2 UV;\n"
      "in vec4 Color;\n"
      "out vec2 Frag_UV;\n"
      "out vec4 Frag_Color;\n"
      "void main()\n"
      "{\n"
      "	Frag_UV = UV;\n"
      "	Frag_Color = Color;\n"
      "	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
      "}\n";

    const GLchar* fragment_shader =
      "#version 330\n"
      "uniform sampler2D Texture;\n"
      "in vec2 Frag_UV;\n"
      "in vec4 Frag_Color;\n"
      "out vec4 Out_Color;\n"
      "void main()\n"
      "{\n"
      "	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
      "}\n";

    ShaderHandle = glCreateProgram();
    VertHandle = glCreateShader(GL_VERTEX_SHADER);
    FragHandle = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(VertHandle, 1, &vertex_shader, 0);
    glShaderSource(FragHandle, 1, &fragment_shader, 0);

    glCompileShader(VertHandle);
    glCompileShader(FragHandle);

    glAttachShader(ShaderHandle, VertHandle);
    glAttachShader(ShaderHandle, FragHandle);
    glLinkProgram(ShaderHandle);

    // Save handles to the uniforms
    AttribLocationTex = glGetUniformLocation(ShaderHandle, "Texture");
    AttribLocationProjMtx = glGetUniformLocation(ShaderHandle, "ProjMtx");
    AttribLocationPosition = glGetAttribLocation(ShaderHandle, "Position");
    AttribLocationUV = glGetAttribLocation(ShaderHandle, "UV");
    AttribLocationColor = glGetAttribLocation(ShaderHandle, "Color");

    glGenBuffers(1, &VboHandle);
    glGenBuffers(1, &ElementsHandle);

    glGenVertexArrays(1, &VaoHandle);
    glBindVertexArray(VaoHandle);
    glBindBuffer(GL_ARRAY_BUFFER, VboHandle);
    glEnableVertexAttribArray(AttribLocationPosition);
    glEnableVertexAttribArray(AttribLocationUV);
    glEnableVertexAttribArray(AttribLocationColor);

    #define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    glVertexAttribPointer(AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
    glVertexAttribPointer(AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
    glVertexAttribPointer(AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
    #undef OFFSETOF
    //------------------------------------------------------------------------/
    // Generate font textures
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    glGenTextures(1, &FontTexture);
    glBindTexture(GL_TEXTURE_2D, FontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    io.Fonts->TexID = (void *)(intptr_t)FontTexture;

    io.Fonts->ClearInputData();
    io.Fonts->ClearTexData();
    //------------------------------------------------------------------------/

    return true;
  }

  bool ImGuiBinding::BindRendering()
  {
    ImGuiIO& io = ImGui::GetIO();

    // We are keeping it null so we don't have to use a static function
    // (Browse over the description!)
    io.RenderDrawListsFn = nullptr;

    return true;
  }

  void ImGuiBinding::RenderDrawLists()
  {
    auto draw_data = ImGui::GetDrawData();

    // 1. Backup the current OpenGL state
    auto currentState = BackupGLState();

    // 2. Setup the next render state: 
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glActiveTexture(GL_TEXTURE0);

    // 2.1 Handle cases of screen coordinates != from framebuffer coordinates
    // (e.g retina displays)
    ImGuiIO& io = ImGui::GetIO();
    float fbHeight = io.DisplaySize.y * io.DisplayFramebufferScale.y;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    // 3. Setup the Orthographic projection matrix
    const glm::mat4x4 orthoProjection = {
      { 2.0f / io.DisplaySize.x, 0.0f,                        0.0f, 00.f },
      { 0.0f,                    2.0f / -io.DisplaySize.y,    0.0f, 0.0f },
      { 0.0f,                    0.0f,                       -1.0f, 0.0f },
      { -1.0f,                   1.0f,                        0.0f, 1.0f },
    };

    // 4. Active the shader program
    glUseProgram(ShaderHandle);
    glUniform1i(AttribLocationTex, 0);
    glUniformMatrix4fv(AttribLocationProjMtx, 1, GL_FALSE, &orthoProjection[0][0]);
    glBindVertexArray(VaoHandle);

    // 5. Update command lists
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
      const ImDrawList* cmd_list = draw_data->CmdLists[n];
      const ImDrawIdx* idx_buffer_offset = 0;

      glBindBuffer(GL_ARRAY_BUFFER, VboHandle);
      glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.size() * sizeof(ImDrawVert), (GLvoid*)&cmd_list->VtxBuffer.front(), GL_STREAM_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsHandle);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx), (GLvoid*)&cmd_list->IdxBuffer.front(), GL_STREAM_DRAW);

      for (const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++)
      {
        if (pcmd->UserCallback)
        {
          pcmd->UserCallback(cmd_list, pcmd);
        }
        else
        {
          glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
          glScissor((int)pcmd->ClipRect.x, (int)(fbHeight - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
          glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer_offset);
        }
        idx_buffer_offset += pcmd->ElemCount;
      }
    }

    // 6. Restore the modified state
    RestoreGLState(currentState);
  }

  void ImGuiBinding::UpdateDisplaySize()
  {
    ImGuiIO& io = ImGui::GetIO();

    // Sets the initial display size
    auto& windowSettings = Window::getInstance()->getSettings();
    io.DisplaySize = ImVec2(static_cast<float>(windowSettings.ScreenWidth),
      static_cast<float>(windowSettings.ScreenHeight));
  }

  bool ImGuiBinding::IsCapturingMouse()
  {
    return ImGui::GetIO().WantCaptureMouse;
  }

  bool ImGuiBinding::IsCapturingKeyboard()
  {
    return ImGui::GetIO().WantCaptureKeyboard;
  }

  OpenGLStateData ImGuiBinding::BackupGLState()
  {
    OpenGLStateData currentState;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentState.lastProgram);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentState.lastTexture);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentState.lastArrayBuffer);
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentState.lastElementArrayBuffer);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentState.lastVertexArray);
    glGetIntegerv(GL_BLEND_SRC, &currentState.lastBlendSrc);
    glGetIntegerv(GL_BLEND_DST, &currentState.lastBlendDst);
    glGetIntegerv(GL_BLEND_EQUATION_RGB, &currentState.lastBlendEquationRGB);
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &currentState.lastBlendEquationAlpha);
    glGetIntegerv(GL_VIEWPORT, currentState.lastViewport);
    currentState.lastEnableBlend = glIsEnabled(GL_BLEND);
    currentState.lastEnableCullFace = glIsEnabled(GL_CULL_FACE);
    currentState.lastEnableDepthTest = glIsEnabled(GL_DEPTH_TEST);
    currentState.lastEnableScissorTest = glIsEnabled(GL_SCISSOR_TEST);
    return currentState;
  }

  void ImGuiBinding::RestoreGLState(const OpenGLStateData & currentState)
  {
    glUseProgram(currentState.lastProgram);
    glBindTexture(GL_TEXTURE_2D, currentState.lastTexture);
    glBindBuffer(GL_ARRAY_BUFFER, currentState.lastArrayBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentState.lastElementArrayBuffer);
    glBindVertexArray(currentState.lastVertexArray);
    glBlendEquationSeparate(currentState.lastBlendEquationRGB, currentState.lastBlendEquationAlpha);
    glBlendFunc(currentState.lastBlendSrc, currentState.lastBlendDst);
    glViewport(currentState.lastViewport[0], currentState.lastViewport[1], 
               (GLsizei)currentState.lastViewport[2], (GLsizei)currentState.lastViewport[3]);
    if (currentState.lastEnableBlend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    if (currentState.lastEnableCullFace) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    if (currentState.lastEnableDepthTest) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    if (currentState.lastEnableScissorTest) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
  }
  
}