#include "Graphics/Model.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Graphics
{
  Model::Model(const char *path, const char *material_path) : isModelLoaded{false}, isMeshReady{false}, model{glm::mat4{1.0f}}, pre_model{glm::mat4{1.0f}}
  {
    if (!loadObj(path, material_path))
    {
      spdlog::error("Failed to load OBJ file: {}", path);
      return;
    }

    loadMesh();

    model_name = shapes[0].name;

    isModelLoaded = true;
  }

  Model::~Model()
  {
  }

  bool Model::loadObj(const char *path, const char *material_path)
  {
    std::string warn;
    std::string err;

    bool success = tinyobj::LoadObj(
        &attrib,
        &shapes,
        &materials, // Pass nullptr instead of a materials vector
        &warn,
        &err,
        path,
        material_path);

    if (!warn.empty())
    {
      spdlog::warn("{}", warn);
    }

    if (materials.empty())
    {
      spdlog::info("No materials loaded. Using default material.");
    }

    if (!err.empty())
    {
      spdlog::error("{}", err);
    }

    if (!success)
    {
      return false;
    }

    return true;
  }

  void Model::loadMesh()
  {
    std::unordered_map<std::string, unsigned int> uniqueVertices;

    for (const auto &shape : shapes)
    {
      for (const auto &index : shape.mesh.indices)
      {
        Vertex vertex;

        // Position
        vertex.position = glm::vec3(
            attrib.vertices[3 * index.vertex_index + 0],
            attrib.vertices[3 * index.vertex_index + 1],
            attrib.vertices[3 * index.vertex_index + 2]);

        // Normal
        if (!attrib.normals.empty())
        {
          vertex.normal = glm::vec3(
              attrib.normals[3 * index.normal_index + 0],
              attrib.normals[3 * index.normal_index + 1],
              attrib.normals[3 * index.normal_index + 2]);
        }

        // Texture Coordinates
        if (!attrib.texcoords.empty())
        {
          vertex.texCoords = glm::vec2(
              attrib.texcoords[2 * index.texcoord_index + 0],
              attrib.texcoords[2 * index.texcoord_index + 1]);
        }

        // Create a unique key for the vertex
        std::ostringstream keyStream;
        keyStream << vertex.position.x << "_" << vertex.position.y << "_" << vertex.position.z << "_"
                  << vertex.normal.x << "_" << vertex.normal.y << "_" << vertex.normal.z << "_"
                  << vertex.texCoords.x << "_" << vertex.texCoords.y;

        std::string key = keyStream.str();

        if (uniqueVertices.find(key) == uniqueVertices.end())
        {
          uniqueVertices[key] = vertices.size();
          vertices.push_back(vertex);
        }

        indices.push_back(uniqueVertices[key]);
      }
    }
  }

  void Model::setupObj()
  {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    isMeshReady = true;

    vertices.clear();
    std::vector<Vertex>().swap(vertices);
  }

  void Model::Draw()
  {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  // Object Manipulation Funcs
  void Model::MoveObject(float x, float y, float z)
  {
    model = glm::translate(model, glm::vec3(x, y, z));
    position = glm::vec3(model[3]);
  }

  void Model::RotateObject(float x, float y, float z, float rad)
  {

    model = glm::rotate(model, rad, glm::vec3(x, y, z)); // Apply the rotation
    rotation = glm::eulerAngles(glm::quat_cast(model));  // Update the rotation angles
  }

  void Model::ScaleObject(float x, float y, float z)
  {

    model = glm::scale(model, glm::vec3(x, y, z));
    scale = glm::vec3(model[0][0], model[1][1], model[2][2]);
  }

  void Model::Apply(std::shared_ptr<Graphics::Shader> &shader)
  {
    shader->SetMat4("model", model);
    model = glm::mat4(1.0f);
  }

  // Get object props
  glm::vec3 Model::GetPosition() const
  {
    return position;
  }

  glm::vec3 Model::GetRotation() const
  {
    return rotation;
  }

  glm::vec3 Model::GetScale() const
  {
    return scale;
  }

  glm::mat4 Model::GetModelMatrix() const
  {
    return model;
  }
};

// namespace Graphics
