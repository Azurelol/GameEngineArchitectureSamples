#include "ImGuiBindingSFML.h"

#include "../Window/Window.h"

namespace Systems {

  bool ImGuiBindingSFML::BindInput()
  {
    // Subscribe for the binding function to be called when the window system is polling for events:
    // http://stackoverflow.com/questions/7582546/using-generic-stdfunction-objects-with-member-functions-in-one-class
    Window::getInstance()->Subscribe(std::bind(&ImGuiBindingSFML::PollEvents, this));
    
    ImGuiIO& io = ImGui::GetIO();

    // Bind the keys used by dear imgui
    io.KeyMap[ImGuiKey_Tab] = sf::Keyboard::Tab;
    io.KeyMap[ImGuiKey_LeftArrow] = sf::Keyboard::Left;
    io.KeyMap[ImGuiKey_RightArrow] = sf::Keyboard::Right;
    io.KeyMap[ImGuiKey_UpArrow] = sf::Keyboard::Up;
    io.KeyMap[ImGuiKey_DownArrow] = sf::Keyboard::Down;
    io.KeyMap[ImGuiKey_Home] = sf::Keyboard::Home;
    io.KeyMap[ImGuiKey_End] = sf::Keyboard::End;
    io.KeyMap[ImGuiKey_Delete] = sf::Keyboard::Delete;
    io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::BackSpace;
    io.KeyMap[ImGuiKey_Enter] = sf::Keyboard::Return;
    io.KeyMap[ImGuiKey_Escape] = sf::Keyboard::Escape;
    io.KeyMap[ImGuiKey_A] = sf::Keyboard::A;
    io.KeyMap[ImGuiKey_C] = sf::Keyboard::C;
    io.KeyMap[ImGuiKey_V] = sf::Keyboard::V;
    io.KeyMap[ImGuiKey_X] = sf::Keyboard::X;
    io.KeyMap[ImGuiKey_Y] = sf::Keyboard::Y;
    io.KeyMap[ImGuiKey_Z] = sf::Keyboard::Z;
    TimeElapsed.restart();

    return true;
  }
  
  void ImGuiBindingSFML::RenderDrawLists()
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

  void ImGuiBindingSFML::PollEvents()
  {
    ImGuiIO& io = ImGui::GetIO();
    auto& event = WindowSFML::getCurrentEvent();

    switch (event.type) {
    case sf::Event::KeyPressed:
      io.KeysDown[event.key.code] = true;
      io.KeyCtrl = event.key.control;
      io.KeyShift = event.key.shift;
      break;

    case sf::Event::KeyReleased:
      io.KeysDown[event.key.code] = false;
      io.KeyCtrl = event.key.control;
      io.KeyShift = event.key.shift;
      break;

    case sf::Event::MouseButtonPressed:
      MousePressed[event.mouseButton.button] = true;
      break;

    case sf::Event::MouseButtonReleased:
      MousePressed[event.mouseButton.button] = false;
      break;

    case sf::Event::MouseWheelMoved:
      io.MouseWheel += static_cast<float>(event.mouseWheel.delta);
      break;

    case sf::Event::TextEntered:
      if (event.text.unicode > 0 && event.text.unicode < 0x10000)
        ImGui::GetIO().AddInputCharacter(event.text.unicode);
      break;

    default:
      break;

    }
  }

  void ImGuiBindingSFML::UpdateTimeStep()
  {
    ImGuiIO& io = ImGui::GetIO();

    // Update time step
    static double time = 0.0f;
    const double currentTime = TimeElapsed.getElapsedTime().asSeconds();
    float deltaTime = static_cast<float>(currentTime - time);
    io.DeltaTime = std::max(deltaTime, 0.f);
    time = currentTime;
  }

  void ImGuiBindingSFML::UpdateInput()
  {
    ImGuiIO& io = ImGui::GetIO();

    // Update inputs
    sf::Vector2i mousePos = sf::Mouse::getPosition(*WindowSFML::getContext());
    io.MousePos = ImVec2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    io.MouseDown[0] = MousePressed[0] || sf::Mouse::isButtonPressed(sf::Mouse::Left);
    io.MouseDown[1] = MousePressed[1] || sf::Mouse::isButtonPressed(sf::Mouse::Right);
  }


  


}