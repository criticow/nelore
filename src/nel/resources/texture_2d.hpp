#pragma once

#include <nelpch.hpp>

class Texture2D
{
  public:
  GLuint handle = 0;
  Texture2D(){};
  Texture2D(const char *path);
  void bind();
  void destroy();

  operator bool() const
  {
    return handle != 0;
  }
};