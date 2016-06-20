#pragma once
#include "..\Objects\Resource.h"

#include <GLEW\glew.h>

namespace Resources {

  class Shader : public Resource {
  public:

    //-----------------------------------------------/
    enum class Type {
      Vertex,
      Fragment
    };
    //-----------------------------------------------/
    // This is a way of associating enums with strings hohoho
    struct TypeInfo {
      std::string Name; int Enum;
      TypeInfo(const std::string& name, int enumeration) : Name(name), Enum(enumeration) {} };
    struct VertexInfo : public TypeInfo { VertexInfo() : TypeInfo("Vertex", GL_VERTEX_SHADER) {} };
    struct FragmentInfo : public TypeInfo { FragmentInfo() : TypeInfo("Fragment", GL_FRAGMENT_SHADER) {} };
    //-----------------------------------------------/
    struct Data {
      std::string Path;
      std::string Code;
      Data(const std::string& path, const std::string& code) :
        Path(path), Code(code) {}
    };                       
    //-------------------------------------------------/
    using Ptr = std::shared_ptr<Shader>;
    //-----------------------------------------------/
    Shader(const std::string& name) : Resource(name) {}
    bool Load(Type shaderType, const std::string& path);
    bool Compile();
    Shader& Use();
    Shader& Unbind();
    GLenum ErrorCheck(std::string message);

    void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
    void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
    void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
    void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

    
  private:
    std::map<Type, Data> ShaderFiles;
    GLuint ShaderProgramID;
    void AssertShaderCompilation(GLuint shader, const std::string& shaderName);
    void AssertShaderProgramLinking(GLuint shaderProgram);

  };

}