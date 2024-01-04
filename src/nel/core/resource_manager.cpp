#include "resource_manager.hpp"

Shader &ResourceManager::getShader(const std::string &name)
{
  ASSERT(this->hasResource<Shader>(name), "Shader not found {}", name);
  return this->shaders[name];
}

Shader &ResourceManager::loadShader(const std::string &name, const char *vShaderPath, const char *fShaderPath)
{
  // Get the code from the shaders files
  std::string vShaderCode = readFile(vShaderPath);
  std::string fShaderCode = readFile(fShaderPath);
  return this->loadShader(name, Shader(vShaderCode.c_str(), fShaderCode.c_str()));
}

Shader &ResourceManager::loadShader(const std::string &name, Shader shader)
{
  this->shaders[name] = shader;
  LOGGER_DEBUG("Created Shader {}", name);
  return this->shaders[name];
}

RenderObject &ResourceManager::getRenderObject(const std::string &name)
{
  ASSERT(this->hasResource<RenderObject>(name), "RenderObject not found {}", name);
  return this->renderObjects[name];
}

RenderObject &ResourceManager::loadRenderObject(const std::string &name, std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
  return this->loadRenderObject(name, RenderObject(vertices, indices));
}

RenderObject &ResourceManager::loadRenderObject(const std::string &name, RenderObject renderObject)
{
  this->renderObjects[name] = renderObject;
  LOGGER_DEBUG("Created RenderObject {}", name);
  return this->renderObjects[name];
}

void ResourceManager::destroy()
{
  for(auto [name, shader] : this->shaders)
  {
    shader.destroy();
  }
  LOGGER_DEBUG("Destroyed {} Shaders", this->shaders.size());

  for(auto [name, renderObject] : this->renderObjects)
  {
    renderObject.destroy();
  }
  LOGGER_DEBUG("Destroyed {} RenderObjects", this->renderObjects.size());

  LOGGER_DEBUG("Destroyed ResourceManager");
}