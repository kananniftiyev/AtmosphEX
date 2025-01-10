#ifndef GRAPHICS_MODEL_HPP_
#define GRAPHICS_MODEL_HPP_

#include "Graphics/Shader.hpp"
#include "Utils/GraphicsUtils.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "include/Mesh.hpp"
#include "include/Model.hpp"

namespace Graphics
{
  struct MeshData
  {
    GLuint VAO;
    std::vector<AutoVert::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<AutoVert::Texture> textures;
  };

  class Model
  {
  private:
    // unsigned int VAO, VBO, EBO;

    // Object Properties
    std::string model_name;
    int vertex_amount;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    // Data
    std::vector<MeshData> meshes;

    // other
    glm::mat4 model_matrix;

    // Helper Funcs
    GLuint setupVAOForMesh(MeshData &data);
    void loadTextures();

  public:
    Model(const std::string &path);
    ~Model();
    void draw(std::shared_ptr<Graphics::Shader> &shader);

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