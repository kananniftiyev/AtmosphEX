#ifndef GRAPHICS_MESH_HPP_
#define GRAPHICS_MESH_HPP_

#include <map>
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include "tinygltf/tiny_gltf.h"

namespace Graphics
{
  class Mesh
  {
  private:
    struct Vertex
    {
      float position[3];
      float normal[3];
      float texCoord[2];
    };

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::map<std::string, GLuint> textures;

  public:
    Mesh(/* args */);

    void Draw() const;
  };

}

#endif // GRAPHICS_MESH_HPP_