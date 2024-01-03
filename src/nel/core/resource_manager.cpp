#include "resource_manager.hpp"

Shader &ResourceManager::getShader(const std::string &name)
{
  ASSERT(this->hasResource<Shader>(name), "Could not find shader with name {}", name);
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
  LOGGER_DEBUG("Create Shader {}", name);
  return this->shaders[name];
}

void ResourceManager::destroy()
{
  for(auto [name, shader] : this->shaders)
  {
    shader.destroy();
  }
  LOGGER_DEBUG("Destroyed {} Shaders", this->shaders.size());

  LOGGER_DEBUG("Destroyed ResourceManager");
}