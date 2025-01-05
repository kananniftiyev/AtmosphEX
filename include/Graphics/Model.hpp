#ifndef GRAPHICS_MODEL_HPP_
#define GRAPHICS_MODEL_HPP_

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
      glm::vec2 tex_coords;
    };

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    // Object Properties
    std::string model_name;
    int vertex_amount;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    // other
    glm::mat4 model;

    // Helper Funcs
    bool loadObj(const char *path, const char *material_path);
    void loadMesh();

    // void loadMaterials();

  public:
    Model(const char *path, const char *material_path);
    ~Model();
    void draw();
    void setupObj();

    // Object manipulation
    void moveObject(float x, float y, float z);
    void rotateObject(float x, float y, float z, float rad);
    void scaleObject(float x, float y, float z);
    void apply(std::shared_ptr<Graphics::Shader> &shader);

    // Object prop funcs
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;
    glm::mat4 getModelMatrix() const;
    std::string getObjectName() const;
    int getObjectVerticesAmount() const;

    // Vars
    bool is_model_ready;
    bool is_model_loaded;
  };
} // namespace Graphics

#endif // GRAPHICS_MODEL_HPP_