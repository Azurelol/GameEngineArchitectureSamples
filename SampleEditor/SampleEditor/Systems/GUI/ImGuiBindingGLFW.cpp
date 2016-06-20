#include "ImGuiBindingGLFW.h"

namespace Systems {

  ImGuiBindingGLFW* ImGuiBindingGLFW::Instance = nullptr;

  ImGuiBindingGLFW::ImGuiBindingGLFW()
  {
    Instance = this;
  }

  ImGuiBindingGLFW::~ImGuiBindingGLFW()
  {
    Instance = nullptr;
  }

  void ImGuiBindingGLFW::PollEvents()
  {
  }

  void ImGuiBindingGLFW::UpdateTimeStep()
  {
    ImGuiIO& io = ImGui::GetIO();
    // Setup time step
    double current_time = glfwGetTime();
    io.DeltaTime = Time > 0.0 ? (float)(current_time - Time) : (float)(1.0f / 60.0f);
    Time = current_time;
  }

  void ImGuiBindingGLFW::UpdateInput()
  {
    ImGuiIO& io = ImGui::GetIO();
    auto window = WindowGLFW::getContext();

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED))
    {
      double mouse_x, mouse_y;
      glfwGetCursorPos(window, &mouse_x, &mouse_y);
      io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);   // Mouse position in screen coordinates (set to -1,-1 if no mouse / on another screen, etc.)
    }
    else
    {
      io.MousePos = ImVec2(-1, -1);
    }

    for (int i = 0; i < 3; i++)
    {
      io.MouseDown[i] = MousePressed[i] || glfwGetMouseButton(window, i) != 0;    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
      MousePressed[i] = false;
    }

    io.MouseWheel = MouseWheel;
    MouseWheel = 0.0f;

    // Hide OS mouse cursor if ImGui is drawing it
    glfwSetInputMode(window, GLFW_CURSOR, io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

  }

  bool ImGuiBindingGLFW::BindInput()
  {
    ImGuiIO& io = ImGui::GetIO();

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;     
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    //io.ImeWindowHandle = glfwGet ::getContext();
    auto window = WindowGLFW::getContext();
    // Set the callbacks
    glfwSetMouseButtonCallback(window, OnMouseButtonCallback);
    glfwSetScrollCallback(window, OnMouseScrollCallback);
    glfwSetKeyCallback(window, OnKeyCallback);
    glfwSetCharCallback(window, OnCharCallback);
    io.SetClipboardTextFn = SetClipboardText;
    io.GetClipboardTextFn = GetClipboardText;

    return true;
  }

  void ImGuiBindingGLFW::RenderDrawLists()
  {
    auto draw_data = ImGui::GetDrawData();

    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    ImGuiIO& io = ImGui::GetIO();
    int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width == 0 || fb_height == 0)
      return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    // Backup GL state
    auto currentState = BackupGLState();

    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glActiveTexture(GL_TEXTURE0);

    // Setup viewport, orthographic projection matrix
    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
    const float ortho_projection[4][4] =
    {
      { 2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
      { 0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
      { 0.0f,                  0.0f,                  -1.0f, 0.0f },
      { -1.0f,                  1.0f,                   0.0f, 1.0f },
    };
    glUseProgram(ShaderHandle);
    glUniform1i(AttribLocationTex, 0);
    glUniformMatrix4fv(AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
    glBindVertexArray(VaoHandle);

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
          glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
          glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
        }
        idx_buffer_offset += pcmd->ElemCount;
      }
    }

    // Restore modified GL state
    RestoreGLState(currentState);
  }
  void ImGuiBindingGLFW::OnMouseButtonCallback(GLFWwindow *, int button, int action, int)
  {
    if (action == GLFW_PRESS && button >= 0 && button < 3)
      Instance->MousePressed[button] = true;
  }

  void ImGuiBindingGLFW::OnMouseScrollCallback(GLFWwindow * window, double xoffset, double yoffset)
  {
    Instance->MouseWheel += static_cast<float>(yoffset); // The fractional mouse wheel, 1.0 unit 5 lines
  }

  void ImGuiBindingGLFW::OnKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
  {
    ImGuiIO& io = ImGui::GetIO();
    if (action == GLFW_PRESS)
      io.KeysDown[key] = true;
    if (action == GLFW_RELEASE)
      io.KeysDown[key] = false;

    (void)mods; // Modifiers are not reliable across systems
    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
  }

  void ImGuiBindingGLFW::OnCharCallback(GLFWwindow * window, unsigned int c)
  {
    ImGuiIO& io = ImGui::GetIO();
    if (c > 0 && c < 0x10000)
      io.AddInputCharacter((unsigned short)c);
  }
  
  const char* ImGuiBindingGLFW::GetClipboardText()
  {
    return glfwGetClipboardString(WindowGLFW::getContext());
  }

  void ImGuiBindingGLFW::SetClipboardText(const char * text)
  {
    glfwSetClipboardString(WindowGLFW::getContext(), text);
  }


}