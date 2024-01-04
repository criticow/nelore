#pragma once

#include <nelpch.hpp>

class Window
{
  public:
  GLFWwindow *handle = nullptr;
  int width;
  int height;
  bool isFramebufferUpdated = false;
  static std::mutex fbMutex;
  Window(){};
  Window(int width, int height, const char *title, bool centered = false);
  void loadOpenGL();
  bool isOpen();
  void swapBuffers();
  void pollEvents();
  void destroy();
  void setTitle(const std::string &title);
  void setUserPointer();
  void close();
  static void framebufferSizeCallback(GLFWwindow *handle, int width, int height);
  static void glDebugOutput(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei len, const char *msg, const void *usrParam);
};