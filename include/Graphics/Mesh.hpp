#ifndef GRAPHICS_MESH_HPP_
#define GRAPHICS_MESH_HPP_

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <map>
#include <iostream>
#include <glad/glad.h>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Graphics
{
  class Mesh
  {
  private:
    struct Vertex
    {
      float position[3];
      float normal[3];
      float texCoords[2];
    };

    std::vector<Vertex>
        vertices;
    std::vector<unsigned int> indices;

    // OpenGL objects
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

  public:
    Mesh(/* args */);

    void Draw() const;
    bool Load(const char *path);
  };

}

#endif // GRAPHICS_MESH_HPP_