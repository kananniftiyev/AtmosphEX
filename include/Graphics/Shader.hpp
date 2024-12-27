#ifndef GRAPHICS_SHADER_HPP_
#define GRAPHICS_SHADER_HPP_

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>

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
  };

}
#endif // GRAPHICS_SHADER_HPP_