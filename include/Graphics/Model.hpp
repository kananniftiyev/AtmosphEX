#ifndef GRAPHICS_MODEL_HPP_
#define GRAPHICS_MODEL_HPP_

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tiny_obj_loader.h>

#include "Graphics/Shader.hpp"

namespace Graphics
{
  class Model
  {
  private:
    struct Vertex
    {
      glm::vec3 position;
      glm::vec3 normal;
      glm::vec2 texCoords;
    };

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    // Object Properties
    glm::vec3 position;
    glm::vec3 rotation;

    // Helper Funcs
    bool loadObj(const char *path);
    void setupObj();
    void loadIndices();
    void loadVertices();

  public:
    Model(const char *path);
    void Draw();
  };
} // namespace Graphics

#endif // GRAPHICS_MODEL_HPP_