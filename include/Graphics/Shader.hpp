#ifndef GRAPHICS_SHADER_HPP_
#define GRAPHICS_SHADER_HPP_

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Graphics
{
  class Shader
  {
  private:
    uint16_t ID;

  public:
    Shader(const char *vert_file, const char *frag_file);
    ~Shader();

    void use() const;
    void remove() const;
    uint16_t getID() const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setInt(const std::string &name, int value) const;
  };

}
#endif // GRAPHICS_SHADER_HPP_