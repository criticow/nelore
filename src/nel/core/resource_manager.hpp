#pragma once

#include <nelpch.hpp>
#include <nel/resources/shader.hpp>
#include <nel/util/file.hpp>

class ResourceManager
{
  public:
  ResourceManager(){};
  
  Shader& getShader(const std::string& name);
  Shader& loadShader(const std::string& name, const char* vShaderPath, const char* fShaderPath);
  Shader& loadShader(const std::string& name, Shader shader);

  template<typename T>
  bool hasResource(const std::string& name)
  {
    if(std::is_same<T, Shader>::value)
    {
      return this->shaders.find(name) != this->shaders.end();
    }
  }

  void destroy();
  private:
  std::unordered_map<std::string, Shader> shaders;
};