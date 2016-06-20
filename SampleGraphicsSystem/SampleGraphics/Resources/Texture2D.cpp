#include "Texture2D.h"

namespace Resources {

  Texture2D::Texture2D() : 
    Width(0), Height(0), InternalFormat(GL_RGBA), ImageFormat(GL_RGBA),
    Wrap_S(GL_CLAMP_TO_EDGE), Wrap_T(GL_CLAMP_TO_EDGE),
    FilterMin(GL_LINEAR_MIPMAP_LINEAR), FilterMax(GL_LINEAR) {}

  void Texture2D::Generate(GLuint width, GLuint height, sf::Image & data)
  {
    this->Width = width;
    this->Height = height;
    GLenum error;

    glGenTextures(1, &this->TextureID);
    error = glGetError();
    if (error)
      Trace("Failed to generate texture ID!");

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, this->TextureID);
    error = glGetError();
    if (error)
      Trace("Failed to bind the texture!");    

    // Generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, width, height, 0,
      this->ImageFormat, GL_UNSIGNED_BYTE, data.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
    error = glGetError();
    if (error)
      Trace("Failed to generate texture!");

    // Set texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->FilterMax);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    Trace("Successfully generated texture!");
  }

  void Texture2D::Bind() const
  {
    glBindTexture(GL_TEXTURE_2D, this->TextureID);
  }
}