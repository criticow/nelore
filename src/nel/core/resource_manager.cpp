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
  LOGGER_DEBUG("Loaded Shader {}", name);
  return this->shaders[name];
}

Texture2D & ResourceManager::getTexture2D(const std::string & name)
{
  ASSERT(this->hasResource<Texture2D>(name), "Texture2D not found {}", name);
  return this->textures2D[name];
}

Texture2D &ResourceManager::loadTexture2D(const std::string &name, const char *texPath)
{
  return this->loadTexture2D(name, Texture2D(texPath));
}

Texture2D &ResourceManager::loadTexture2D(const std::string &name, Texture2D texture)
{
  this->textures2D[name] = texture;
  LOGGER_DEBUG("Loaded Texture2D {}", name);
  return this->textures2D[name];
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
  LOGGER_DEBUG("Loaded RenderObject {}", name);
  return this->renderObjects[name];
}

Model &ResourceManager::getModel(const std::string &name)
{
  ASSERT(this->hasResource<Model>(name), "Model not found {}", name);
  return this->models[name];
}

Model &ResourceManager::loadModel(const std::string &name, const char *modelPath)
{
  return this->loadModel(name, Model(modelPath, this));
}

Model &ResourceManager::loadModel(const std::string &name, Model model)
{
  this->models[name] = model;
  LOGGER_DEBUG("Loaded Model {}", name);
  return this->models[name];
}

Framebuffer &ResourceManager::getFramebuffer(const std::string &name)
{
  ASSERT(this->hasResource<Framebuffer>(name), "Framebuffer not found {}",name);
  return this->framebuffers[name];
}

Framebuffer &ResourceManager::loadFramebuffer(const std::string &name, Texture2D texture)
{
  return this->loadFramebuffer(name, Framebuffer(texture));
}

Framebuffer &ResourceManager::loadFramebuffer(const std::string &name, Framebuffer framebuffer)
{
  this->framebuffers[name] = framebuffer;
  LOGGER_DEBUG("Loaded Framebuffer {}", name);
  return this->framebuffers[name];
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

  for(auto [name, texture2D] : this->textures2D)
  {
    texture2D.destroy();
  }
  LOGGER_DEBUG("Destroyed {} Textures2D", this->textures2D.size());

  for(auto [name, framebuffer] : this->framebuffers)
  {
    framebuffer.destroy();
  }
  LOGGER_DEBUG("Destroyed {} Framebuffers", this->framebuffers.size());

  LOGGER_DEBUG("Destroyed ResourceManager");
}