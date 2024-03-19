#include "model.hpp"

#include <nel/core/resource_manager.hpp>

Model::Model(const char *path, ResourceManager *resourceManager)
{
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  ASSERT(scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode, "Could not load model {}", path);

  aiMesh *mesh = scene->mMeshes[scene->mRootNode->mMeshes[0]];

  this->mesh.name = mesh->mName.C_Str();

  // Parsing vertices
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

  // Parsing indices
  this->mesh.indices.reserve(mesh->mNumFaces * mesh->mFaces[0].mNumIndices);
  for(size_t i = 0; i < mesh->mNumFaces; i++)
  {
    for(size_t j = 0; j < mesh->mFaces[i].mNumIndices; j++)
    {
      this->mesh.indices.push_back(mesh->mFaces[i].mIndices[j]);
    }
  }

  // Default Material
  this->material.specularColor = glm::vec3(0.5f);
  this->material.diffuseColor = glm::vec3(0.207f);
  this->material.specularColor = glm::vec3(0.5f);
  this->material.shininess = 250.0f;

  // Parsing material/textures
  aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
  if(mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
  {
    aiString str;
    mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
    std::string path = str.C_Str();
    std::string texName = path.substr(path.find_last_of("/") + 1);
    path = "data/textures/" + texName;

    if(resourceManager) // Load using resource manager
    {
      if(resourceManager->hasResource<Texture2D>(texName)) // Texture already exists
      {
        this->material.diffuseTexture = &resourceManager->getTexture2D(texName);
      }
      else // Create a new texture
      {
        this->material.diffuseTexture=  &resourceManager->loadTexture2D(texName, path.c_str());
      }
    }
    else // Standalone loading
    {
      this->material.diffuseTexture = new Texture2D(path.c_str());
    }
  }

  importer.FreeScene();
}