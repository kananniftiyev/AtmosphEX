#include "Utils/GraphicsUtils.hpp"

namespace Utils
{
  long get_mem_usage()
  {
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // in KB
  }

  void setFullScreen(std::shared_ptr<GLFWwindow> &window, int &width, int &height)
  {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    // Get the video mode of the monitor (resolution)
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwGetWindowSize(window.get(), &width, &height);

    // Make the window fullscreen by setting it to the monitor's resolution
    glfwSetWindowMonitor(window.get(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

    width = mode->width;
    height = mode->height;
  }

  void setWindowed(std::shared_ptr<GLFWwindow> &window, int &width, int &height)
  {

    glfwSetWindowMonitor(window.get(), nullptr, 0, 0, width, height, 0);
  }
} // namespace Utils
