#include "Graphics/Shader.hpp"

namespace Graphics
{
  Shader::Shader(const char *vert_file, const char *frag_file)
  {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
      // open files
      vShaderFile.open(vert_file);
      fShaderFile.open(frag_file);
      std::stringstream vShaderStream, fShaderStream;
      // read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // convert stream into string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
      spdlog::error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: {}", e.what());
    }

    spdlog::info("Loading vertex shader from: {}", vert_file);
    spdlog::info("Loading fragment shader from: {}", frag_file);

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    uint16_t vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
      spdlog::error("ERROR::SHADER::Vertex Shader Compilation Failed:\n{}", infoLog);
    }
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
      spdlog::error("ERROR::SHADER::Fragment Shader Compilation Failed:\n{}", infoLog);
    }
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(ID, 512, nullptr, infoLog);
      spdlog::error("ERROR::SHADER::Shader Program Linking Failed:\n{}", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  void Shader::Use() const
  {
    glUseProgram(ID);
  }

  void Shader::Remove() const {}

  uint16_t Shader::GetID() const
  {
    return ID;
  }

  void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
  {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void Shader::SetVec3(const std::string &name, float x, float y, float z) const
  {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
  }

  void Shader::SetInt(const std::string &name, int value) const
  {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

} // namespace Graphics
