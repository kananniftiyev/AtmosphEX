#include "Graphics/Model.hpp"

namespace Graphics
{
  Model::Model(const std::string &path) : is_model_loaded{false}, is_model_ready{false}, model_matrix{glm::mat4{1.0f}}, vertex_amount{0}
  {
    AutoVert::Model model(path);

    for (const auto &mesh : model.meshes)
    {
      MeshData mesh_data;
      mesh_data.vertices = mesh.getVertecies();
      mesh_data.indices = mesh.getIndices();
      mesh_data.textures = mesh.getTextures();
      mesh_data.VAO = setupVAOForMesh(mesh_data);

      meshes.push_back(mesh_data);

      vertex_amount = mesh_data.vertices.size();
    }

    position = glm::vec3(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);
    is_model_loaded = true;
  }

  Model::~Model()
  {
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteVertexArrays(1, &VAO);
  }

  GLuint Model::setupVAOForMesh(MeshData &data)
  {
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(AutoVert::Vertex), &data.vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(unsigned int), &data.indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AutoVert::Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AutoVert::Vertex), (void *)offsetof(AutoVert::Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AutoVert::Vertex), (void *)offsetof(AutoVert::Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return VAO;
  }

  void Model::loadTextures()
  {
  }

  void Model::draw(std::shared_ptr<Graphics::Shader> &shader)
  {

    for (const auto &mesh : meshes)
    {
      unsigned int diffuseNr = 1;
      unsigned int specularNr = 1;
      unsigned int normalNr = 1;
      unsigned int heightNr = 1;
      for (size_t i = 0; i < mesh.textures.size(); i++)
      {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = mesh.textures[i].type;
        if (name == "texture_diffuse")
          number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
          number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
          number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
          number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        shader->setInt((name + number).c_str(), static_cast<int>(i));
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
      }
    }
  }

  // Object Manipulation Funcs
  void Model::moveObject(float x, float y, float z)
  {
    model_matrix = glm::translate(model_matrix, glm::vec3(x, y, z));
    position = glm::vec3(model_matrix[3]);
  }

  void Model::rotateObject(float x, float y, float z, float rad)
  {

    model_matrix = glm::rotate(model_matrix, rad, glm::vec3(x, y, z)); // Apply the rotation
    rotation = glm::eulerAngles(glm::quat_cast(model_matrix));         // Update the rotation angles
  }

  void Model::scaleObject(float x, float y, float z)
  {

    model_matrix = glm::scale(model_matrix, glm::vec3(x, y, z));
    scale = glm::vec3(model_matrix[0][0], model_matrix[1][1], model_matrix[2][2]);
  }

  void Model::apply(std::shared_ptr<Graphics::Shader> &shader)
  {
    shader->setMat4("model", model_matrix);
    model_matrix = glm::mat4(1.0f);
  }

  // Get object props
  glm::vec3 Model::getPosition() const
  {
    return position;
  }

  glm::vec3 Model::getRotation() const
  {
    return rotation;
  }

  glm::vec3 Model::getScale() const
  {
    return scale;
  }

  glm::mat4 Model::getModelMatrix() const
  {
    return model_matrix;
  }

  std::string Model::getObjectName() const
  {
    return model_name;
  }

  int Model::getObjectVerticesAmount() const
  {
    return vertex_amount;
  }
};

// namespace Graphics
