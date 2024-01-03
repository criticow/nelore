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
  static void framebufferSizeCallback(GLFWwindow *handle, int width, int height);
};