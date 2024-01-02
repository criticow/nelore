#include "window.hpp"

Window::Window(int width, int height, const char* title, bool centered)
{
  ASSERT(glfwInit(), "Could not initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
  ASSERT(this->handle, "Could not create window");
  LOGGER_DEBUG("Created Window");

  if(centered)
  {
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    int offsetX, offsetY, windowWidth, windowHeight;

    glfwGetMonitorPos(primaryMonitor, &offsetX, &offsetY);
    glfwGetWindowSize(this->handle, &windowWidth, &windowHeight);
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
    glfwSetWindowPos(this->handle, offsetX + (mode->width - windowWidth) / 2, offsetY + (mode->height - windowHeight) / 2);
    LOGGER_DEBUG("Centered Window");
  }
}

void Window::loadOpenGL()
{
  glfwMakeContextCurrent(this->handle);

  ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Could not load OpenGL");
  LOGGER_DEBUG("Loaded OpenGL: {}.{}", GLVersion.major, GLVersion.minor);
}

bool Window::isOpen()
{
  return !glfwWindowShouldClose(this->handle);
}

void Window::swapBuffers()
{
  glfwSwapBuffers(this->handle);
}

void Window::pollEvents()
{
  glfwPollEvents();
}

void Window::destroy()
{
  glfwTerminate();
}

void Window::setTitle(const std::string &title)
{
  glfwSetWindowTitle(this->handle, title.c_str());
}
