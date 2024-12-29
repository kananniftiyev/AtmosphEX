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

    void Use() const;
    void Remove() const;
    uint16_t GetID() const;
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;
  };

}
#endif // GRAPHICS_SHADER_HPP_