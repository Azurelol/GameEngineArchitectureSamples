#include "ImGuiBindingSDL.h"

namespace Systems {

  ImGuiBindingSDL* ImGuiBindingSDL::Instance = nullptr;

  ImGuiBindingSDL::ImGuiBindingSDL()
  {
    Instance = this;
  }

  ImGuiBindingSDL::~ImGuiBindingSDL()
  {
    Instance = nullptr;
  }

  bool ImGuiBindingSDL::BindInput()
  {
    ImGuiIO& io = ImGui::GetIO();

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
    io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;    
    io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
    io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
    io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
    io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
    io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
    io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
    io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
    io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
    io.KeyMap[ImGuiKey_A] = SDLK_a;
    io.KeyMap[ImGuiKey_C] = SDLK_c;
    io.KeyMap[ImGuiKey_V] = SDLK_v;
    io.KeyMap[ImGuiKey_X] = SDLK_x;
    io.KeyMap[ImGuiKey_Y] = SDLK_y;
    io.KeyMap[ImGuiKey_Z] = SDLK_z;

    // Bind the callbacks
    io.SetClipboardTextFn = SetClipboardText;
    io.GetClipboardTextFn = GetClipboardText;

    return true;
  }

  void ImGuiBindingSDL::RenderDrawLists()
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

    // Setup orthographic projection matrix
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

    RestoreGLState(currentState);

  }


  void ImGuiBindingSDL::PollEvents()
  {
    ImGuiIO& io = ImGui::GetIO();
    auto& event = WindowSDL::getCurrentEvent();

    switch (event.type)
    {
    case SDL_MOUSEWHEEL:
    {
      if (event.wheel.y > 0)
        MouseWheel = 1;
      if (event.wheel.y < 0)
        MouseWheel = -1;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
      if (event.button.button == SDL_BUTTON_LEFT) MousePressed[0] = true;
      if (event.button.button == SDL_BUTTON_RIGHT) MousePressed[1] = true;
      if (event.button.button == SDL_BUTTON_MIDDLE) MousePressed[2] = true;
    }

    case SDL_MOUSEBUTTONUP:
    {
      if (event.button.button == SDL_BUTTON_LEFT) MousePressed[0] = false;
      if (event.button.button == SDL_BUTTON_RIGHT) MousePressed[1] = false;
      if (event.button.button == SDL_BUTTON_MIDDLE) MousePressed[2] = false;
    }

    case SDL_TEXTINPUT:
      io.AddInputCharactersUTF8(event.text.text);

    case SDL_KEYDOWN: 
    {
      int key = event.key.keysym.sym & ~SDLK_SCANCODE_MASK;
      io.KeysDown[key] = (event.type == SDL_KEYDOWN);
      io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
      io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
      io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
      io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
    }

    case SDL_KEYUP:
    {
      int key = event.key.keysym.sym & ~SDLK_SCANCODE_MASK;
      io.KeysDown[key] = (event.type == SDL_KEYDOWN);
      io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
      io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
      io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
      io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);    }
    }

  }

  void ImGuiBindingSDL::UpdateTimeStep()
  {
    ImGuiIO& io = ImGui::GetIO();
    // Setup time step
    Uint32	time = SDL_GetTicks();
    double current_time = time / 1000.0;
    io.DeltaTime = Time > 0.0 ? (float)(current_time - Time) : (float)(1.0f / 60.0f);
    Time = current_time;
  }

  void ImGuiBindingSDL::UpdateInput()
  {
    ImGuiIO& io = ImGui::GetIO();
    auto window = WindowSDL::getContext();

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from SDL_PollEvent())
    int mx, my;
    Uint32 mouseMask = SDL_GetMouseState(&mx, &my);
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS)
      io.MousePos = ImVec2((float)mx, (float)my);   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
    else
      io.MousePos = ImVec2(-1, -1);

    io.MouseDown[0] = MousePressed[0] || (mouseMask & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;		// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
    io.MouseDown[1] = MousePressed[1] || (mouseMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
    io.MouseDown[2] = MousePressed[2] || (mouseMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
    MousePressed[0] = MousePressed[1] = MousePressed[2] = false;

    io.MouseWheel = MouseWheel;
    MouseWheel = 0.0f;

    // Hide OS mouse cursor if ImGui is drawing it
    SDL_ShowCursor(io.MouseDrawCursor ? 0 : 1);
  }

  const char * ImGuiBindingSDL::GetClipboardText()
  {
    return SDL_GetClipboardText();
  }

  void ImGuiBindingSDL::SetClipboardText(const char * text)
  {
    SDL_SetClipboardText(text);
  }
}