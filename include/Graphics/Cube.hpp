#ifndef GRAPHICS_CUBE_HPP_
#define GRAPHICS_CUBE_HPP_

#include <glad/glad.h>
#include <iostream>

namespace Graphics
{
  class Cube
  {
  private:
    GLuint VAO, VBO, EBO;

  public:
    Cube();
    void Draw() const;
  };

}
#endif // GRAPHICS_CUBE_HPP_