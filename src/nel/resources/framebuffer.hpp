#pragma once

#include <nelpch.hpp>
#include <nel/resources/texture_2d.hpp>

class Framebuffer
{
  public:
  GLuint handle;
  Framebuffer(){};
  Framebuffer(Texture2D texture);
  void bind();
  void destroy();
};