#include "Sprite.h"

#include "Transform.h"

namespace Components {
    
  // All about hiding the implementation details from the class declaration, baby!
  struct Sprite::RenderSettings {
    GLuint VAO, VBO;
  };

  //--------------------------------------------------------------------------/
  // Initialize static members
  Sprite::RenderSettings Sprite::Settings;
  Resources::Shader::Ptr Sprite::Shader;
  //--------------------------------------------------------------------------/

  void Sprite::Configure()
  {
    Trace("Compiling the Shader, setting up the VAO, VBO!");

    // Construct the shader object and load vertex and fragment shaders onto it
    Shader.reset(new Resources::Shader("SpriteShader"));
    std::string vertexPath = "Resources\\Shaders\\Sprite.vert";
    std::string fragmentPath = "Resources\\Shaders\\Sprite.frag";
    Shader->Load(Resources::Shader::Type::Vertex, vertexPath);
    Shader->Load(Resources::Shader::Type::Fragment, fragmentPath);

    // Compile the shader
    Shader->Compile();

    // We define a set of vertices with (0,0) coordinate being the top-left corner
    // of the quad. Transformations start from the top-left position
    GLfloat vertices[] {
      // Position,      Texture
      -.5f, -.5f,      0.0f, 0.0f,
      .5f, -.5f,      1.0f, 0.0f,
      .5f,  .5f,      1.0f, 1.0f,
      -.5f,  .5f,      0.0f, 1.0f,
    };
    // Next, we simply send the vertices to the GPU and 
    // configure the vertex attributes, which in this case is a single vertex attribute.
    glGenVertexArrays(1, &Settings.VAO);
    glGenBuffers(1, &Settings.VBO);

    glBindBuffer(GL_ARRAY_BUFFER, Settings.VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(Settings.VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

    // Unbinds the VAO, VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void Sprite::SetUniforms(const Camera * camera)
  {
    auto& translation = TransformComponent->getTranslation();
    auto& rotation = TransformComponent->getRotation();
    auto& scale = TransformComponent->getScale();

    // Create the model matrix
    Mat4 modelMtx;
    modelMtx = glm::translate(modelMtx, glm::vec3(translation.x, translation.y, 0.0f));
    modelMtx = glm::rotate(modelMtx, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelMtx = glm::rotate(modelMtx, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    modelMtx = glm::scale(modelMtx, glm::vec3(scale.x, scale.y, 0.0f));

    // Activate the shader
    Shader->Use();

    // Update the uniforms
    Shader->SetMatrix4("model", modelMtx);
    Shader->SetMatrix4("view", camera->getViewMatrix());
    Shader->SetMatrix4("projection", camera->getProjectionMatrix());
    Shader->SetVector4f("spriteColor", Color);
    Shader->SetInteger("image", 0);
  }
  
  void Sprite::Draw()
  {
    //return;
    auto& texture = SpriteSourceHandle->getTexture();

    // Set the active texture
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    // Bind the vertex array
    glBindVertexArray(Settings.VAO);
    // Draw the array
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Unbind the vertex array
    glBindVertexArray(0);
  }

}