#ifndef GRAPHICS_MODEL_HPP_
#define GRAPHICS_MODEL_HPP_

#include <iostream>
#include <vector>
#include <memory>

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
    std::string model_name;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    // other
    glm::mat4 model;
    glm::mat4 pre_model;

    int scaleCount;
    int rotateCount;

    // Helper Funcs
    bool loadObj(const char *path, const char *material_path);
    void loadMesh();

    // void loadMaterials();

  public:
    Model(const char *path, const char *material_path);
    ~Model();
    void Draw();
    void setupObj();

    // Object manipulation
    void MoveObject(float x, float y, float z);
    void RotateObject(float x, float y, float z, float rad);
    void ScaleObject(float x, float y, float z);
    void Apply(std::shared_ptr<Graphics::Shader> &shader);

    // Object prop funcs
    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetScale() const;
    glm::mat4 GetModelMatrix() const;

    // Vars
    bool isMeshReady;
    bool isModelLoaded;
  };
} // namespace Graphics

#endif // GRAPHICS_MODEL_HPP_