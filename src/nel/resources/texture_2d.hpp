#pragma once

#include <nelpch.hpp>

class Texture2D
{
  public:
  GLuint handle = 0;
  Texture2D(){};
  Texture2D(const char *path);
  // Shadow Map texture
  Texture2D(GLsizei width, GLsizei height);
  void bind(GLenum position = GL_TEXTURE0);
  void destroy();

  // operator bool() const
  // {
  //   return handle != 0;
  // }
};