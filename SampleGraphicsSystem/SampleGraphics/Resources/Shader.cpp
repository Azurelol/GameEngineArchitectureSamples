#include "Shader.h"

#include <fstream> // ifstream
#include <sstream> // stringstream

namespace Resources {

  bool Shader::Load(Type shaderType, const std::string & path)
  {
    std::ifstream shaderFile;

    // Ensure the objects can throw exceptions
    shaderFile.exceptions(std::ifstream::badbit);

    try {
      shaderFile.open(path);
      // Read the contents of the file into the sstream object
      std::stringstream shaderStream;
      shaderStream << shaderFile.rdbuf();
      // Close the file
      shaderFile.close();
      // Construct and object Store the shader code within it
      Data shaderData(path, shaderStream.str());
      // Add it to our collections of shaders
      ShaderFiles.insert(std::pair<Type, Data>(shaderType, shaderData));
      TraceObject("Loaded '" + path + "'");
    }

    catch (std::ifstream::failure e) {
      TraceObject("Failed!");
      return false;
    }

    return true;
  }

  bool Shader::Compile()
  {
    std::vector<GLuint> shaders;

    // Compile all the shaders
    for (auto& shaderFile : ShaderFiles) {     

      // Associate the type enum with the info needed to create it
      TypeInfo* info = nullptr;
      switch (shaderFile.first) {
      case Type::Vertex:
        info = new VertexInfo();
        break;
      case Type::Fragment:
        info = new FragmentInfo();
        break;
      }

      // Create the shader
      GLuint shader;
      shader = glCreateShader(info->Enum);
      const GLchar* code = shaderFile.second.Code.c_str();
      glShaderSource(shader, 1, &code, NULL);
      glCompileShader(shader);
      AssertShaderCompilation(shader, info->Name);
      shaders.push_back(shader);

      // TL Note: Okay I realized doing it this way was more of a mental gymnastics
      // exercise to see if there was a neat way of associating enums with strings.
      // You can hate me but don't hate the code~
      delete info;
    }
        
    // Create the shader program
    this->ShaderProgramID = glCreateProgram();
    // Attach all the shaders to it
    for (auto& shader : shaders) {
      glAttachShader(this->ShaderProgramID, shader);
      ErrorCheck("Failed to attach?");
    }
    glLinkProgram(this->ShaderProgramID);
    AssertShaderProgramLinking(this->ShaderProgramID);
    ErrorCheck("What");
    

    // Delete the shaders now that they are linked and no longer necessary
    for (auto& shader : shaders) {
      glDeleteShader(shader);
    }

    return true;
  }

  Shader & Shader::Use()
  {    
    // Activates the shader
    glUseProgram(this->ShaderProgramID);
    return *this;
  }

  Shader & Shader::Unbind()
  {
    glUseProgram(0);
    return *this;
  }

  GLenum Shader::ErrorCheck(std::string message)
  {
    GLenum error;
    error = glGetError();
    if (error) {
      TraceObject(message);
    }
    return error;
  }

  void Shader::AssertShaderCompilation(GLuint shader, const std::string & shaderName)
  {
    GLint success;       // Define an integer to indicate success
    GLchar infoLog[512]; // Container for the error messages (if any)

    // Check if compilation was successful.
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success) {
      TraceObject("'" + shaderName + " compiled!");
    }
    else {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      TraceObject("'" + shaderName + " failed to compile!");
      TraceObject(infoLog);
    }
  }

  void Shader::AssertShaderProgramLinking(GLuint shaderProgram)
  {
    GLint success;       // Define an integer to indicate success
    GLchar infoLog[512]; // Container for the error messages (if any)

                         // Check if compilation was successful.
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (success) {
      TraceObject("linked successfully!");
    }
    else {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      TraceObject("failed to link!");
      TraceObject(infoLog);
    }
  }
}