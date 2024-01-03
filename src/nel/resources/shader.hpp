#pragma once

#include <nelpch.hpp>

class Shader
{
  public:
  Shader(){};
  Shader(const char *vShaderData, const char *fShaderData);
  void use();
  void destroy();
  void setInt(const std::string &name, GLint value);
  void setFloat(const std::string &name, glm::vec2 value);
  void setFloat(const std::string &name, glm::vec3 value);
  void setFloat(const std::string &name, glm::vec4 value);
  void setMatrix(const std::string &name, glm::mat4 value);

  private:
  GLuint handle;
  std::unordered_map<std::string, GLint> locations;

  GLint getLocation(const std::string &name);
  void validate(GLuint handle, const std::string &type);
};