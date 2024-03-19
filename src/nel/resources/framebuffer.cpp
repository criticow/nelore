#include "framebuffer.hpp"

Framebuffer::Framebuffer(Texture2D texture)
{
  glGenFramebuffers(1, &this->handle);
  glBindFramebuffer(GL_FRAMEBUFFER, this->handle);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.handle, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, this->handle);
}

void Framebuffer::destroy()
{
  glDeleteFramebuffers(1, &this->handle);
}
