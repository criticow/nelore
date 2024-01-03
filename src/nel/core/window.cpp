#include "window.hpp"

std::mutex Window::fbMutex;

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

  // Window callbacks
  glfwSetFramebufferSizeCallback(this->handle, this->framebufferSizeCallback);
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
  LOGGER_DEBUG("Destroyed Window");
}

void Window::setTitle(const std::string &title)
{
  glfwSetWindowTitle(this->handle, title.c_str());
}

void Window::setUserPointer()
{
  glfwSetWindowUserPointer(this->handle, this);
}

void Window::close()
{
  glfwSetWindowShouldClose(this->handle, GLFW_TRUE);
}

void Window::framebufferSizeCallback(GLFWwindow *handle, int width, int height)
{
  // Do nothing
  if(width == 0 || height == 0)
  {
    return;
  }

  Window *windowPointer = reinterpret_cast<Window *>(glfwGetWindowUserPointer(handle));
  ASSERT(windowPointer, "Could not find window user pointer");

  windowPointer->fbMutex.lock();
  windowPointer->isFramebufferUpdated = true;
  windowPointer->width = width;
  windowPointer->height = height;
  windowPointer->fbMutex.unlock();
}