#include "Graphics/Mesh.hpp"

namespace Graphics
{
  Mesh::Mesh() : VAO(0), VBO(0), EBO(0) {}

  bool Mesh::Load(const char *path)
  {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                                 aiProcess_GenNormals |
                                                 aiProcess_FlipUVs);

    if (!scene)
      return false;

    auto mesh = scene->mMeshes[0]; // Get first mesh

    // Get vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
      Vertex vertex;
      vertex.position[0] = mesh->mVertices[i].x;
      vertex.position[1] = mesh->mVertices[i].y;
      vertex.position[2] = mesh->mVertices[i].z;

      vertex.normal[0] = mesh->mNormals[i].x;
      vertex.normal[1] = mesh->mNormals[i].y;
      vertex.normal[2] = mesh->mNormals[i].z;

      if (mesh->mTextureCoords[0])
      {
        vertex.texCoords[0] = mesh->mTextureCoords[0][i].x;
        vertex.texCoords[1] = mesh->mTextureCoords[0][i].y;
      }

      vertices.push_back(vertex);
    }

    // Get indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
      aiFace face = mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }

    // Setup buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // Normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    // Texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

    return true;
  }

  void Mesh::Draw() const
  {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
} // namespace Graphics
