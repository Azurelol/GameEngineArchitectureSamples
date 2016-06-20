#include "Shader.h"

namespace Resources {


  void Shader::SetFloat(const GLchar * name, GLfloat value, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniform1f(glGetUniformLocation(this->ShaderProgramID, name), value);
  }

  void Shader::SetInteger(const GLchar *name, GLint value, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniform1i(glGetUniformLocation(this->ShaderProgramID, name), value);
  }

  void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniform2f(glGetUniformLocation(this->ShaderProgramID, name), x, y);
  }

  void Shader::SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniform2f(glGetUniformLocation(this->ShaderProgramID, name), value.x, value.y);
  }

  void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniform3f(glGetUniformLocation(this->ShaderProgramID, name), x, y, z);
  }

  void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniform3f(glGetUniformLocation(this->ShaderProgramID, name), value.x, value.y, value.z);
  }

  void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniform4f(glGetUniformLocation(this->ShaderProgramID, name), x, y, z, w);
  }

  void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniform4f(glGetUniformLocation(this->ShaderProgramID, name), value.x, value.y, value.z, value.w);
  }

  void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader) {
    if (useShader)
      this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ShaderProgramID, name), 1, GL_FALSE, glm::value_ptr(matrix));
  }


}