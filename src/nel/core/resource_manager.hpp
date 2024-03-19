#pragma once

#include <nelpch.hpp>
#include <nel/resources/shader.hpp>
#include <nel/resources/render_object.hpp>
#include <nel/resources/model.hpp>
#include <nel/resources/texture_2d.hpp>
#include <nel/resources/framebuffer.hpp>
#include <nel/util/file.hpp>

class ResourceManager
{
  public:
  ResourceManager(){};
  
  Shader& getShader(const std::string& name);
  Shader& loadShader(const std::string& name, const char* vShaderPath, const char* fShaderPath);
  Shader& loadShader(const std::string& name, Shader shader);

  Texture2D& getTexture2D(const std::string& name);
  Texture2D& loadTexture2D(const std::string& name, const char* texPath);
  Texture2D& loadTexture2D(const std::string& name, Texture2D texture);

  RenderObject& getRenderObject(const std::string& name);
  RenderObject& loadRenderObject(const std::string& name, std::vector<Vertex> vertices, std::vector<GLuint> indices);
  RenderObject& loadRenderObject(const std::string& name, RenderObject renderObject);

  Model& getModel(const std::string &name);
  Model& loadModel(const std::string &name, const char *modelPath);
  Model& loadModel(const std::string &name, Model model);

  Framebuffer& getFramebuffer(const std::string &name);
  Framebuffer& loadFramebuffer(const std::string &name, Texture2D texture);
  Framebuffer& loadFramebuffer(const std::string &name, Framebuffer framebuffer);

  template<typename T>
  bool hasResource(const std::string& name)
  {
    if(std::is_same<T, Shader>::value)
    {
      return this->shaders.find(name) != this->shaders.end();
    }

    if(std::is_same<T, Texture2D>::value)
    {
      return this->textures2D.find(name) != this->textures2D.end();
    }

    if(std::is_same<T, RenderObject>::value)
    {
      return this->renderObjects.find(name) != this->renderObjects.end();
    }

    if(std::is_same<T, Model>::value)
    {
      return this->models.find(name) != this->models.end();
    }

    if(std::is_same<T, Framebuffer>::value)
    {
      return this->framebuffers.find(name) != this->framebuffers.end();
    }
  }

  void destroy();
  private:
  std::unordered_map<std::string, Shader> shaders;
  std::unordered_map<std::string, RenderObject> renderObjects;
  std::unordered_map<std::string, Model> models;
  std::unordered_map<std::string, Texture2D> textures2D;
  std::unordered_map<std::string, Framebuffer> framebuffers;
};