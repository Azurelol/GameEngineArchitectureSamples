/******************************************************************************/
/*!
@file   Texture2D.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   9/16/2015
@brief  The texture class stores and configures a texture in OpenGL.
@note   "http://learnopengl.com/#!Getting-started/Textures"
@copyright Copyright 2015, DigiPen Institute of Technology. All rights reserved.
@todo   Remove the Find method. Texture2D shoudln't derive from Resource?

*/
/******************************************************************************/
#pragma once
#include "../Objects/Resource.h"

#include <GLEW\glew.h>
#include <SFML\Graphics\Image.hpp> // For loading image files into memory

namespace Resources {

  class Texture2D {    

  public:

    GLuint TextureID;      // Holds the ID of the texture object, used for all 
                           // texture operations to reference to this particular texture.   
    GLuint Width, Height;  // Texture image dimensions
    GLuint InternalFormat; // Format of texture object
    GLuint ImageFormat;    // Format of loaded image
    GLuint Wrap_S;         // Wrapping mode on S axis
    GLuint Wrap_T;         // Wrapping mode on T axis
    GLuint FilterMin;      // Filtering mode if texture pixels < screen pixels
    GLuint FilterMax;      // Filtering mode if texture pixels > screen pixels 


    // Constructor (sets default texture mode)
    Texture2D();
    // Generates texture from image data
    void Generate(GLuint width, GLuint height, sf::Image& data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;



  };

}