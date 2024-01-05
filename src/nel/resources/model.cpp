#include "model.hpp"

Model::Model(const char *path)
{
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  ASSERT(scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode, "Could not load model {}", path);

  aiMesh *mesh = scene->mMeshes[scene->mRootNode->mMeshes[0]];

  this->mesh.name = mesh->mName.C_Str();

  this->mesh.vertices.reserve(mesh->mNumVertices);
  for(size_t i = 0; i < mesh->mNumVertices; i++)
  {
    aiVector2D texCoords(0.0f);
    if(mesh->mTextureCoords[0])
    {
      texCoords.x = mesh->mTextureCoords[0][i].x;
      texCoords.y = mesh->mTextureCoords[0][i].y;
    }

    this->mesh.vertices.emplace_back(
      glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
      glm::vec2(texCoords.x, texCoords.y),
      glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)
    );
  }

  this->mesh.indices.reserve(mesh->mNumFaces * mesh->mFaces[0].mNumIndices);
  for(size_t i = 0; i < mesh->mNumFaces; i++)
  {
    for(size_t j = 0; j < mesh->mFaces[i].mNumIndices; j++)
    {
      this->mesh.indices.push_back(mesh->mFaces[i].mIndices[j]);
    }
  }

  importer.FreeScene();
}