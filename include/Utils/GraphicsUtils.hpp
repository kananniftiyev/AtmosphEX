#ifndef UTILS_GRAPHICSUTILS_HPP_
#define UTILS_GRAPHICSUTILS_HPP_

#include <iostream>
#include <sys/resource.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Utils
{
  /**
   * @brief Get the current memory usage of the application.
   *
   * This function uses the `getrusage` system call to fetch the memory usage
   * of the current process.
   *
   * @return The memory usage in kilobytes (KB). Returns -1 if the operation fails.
   */
  long get_mem_usage();

  /**
   * @brief Switch a window to fullscreen mode.
   *
   * This function sets the specified GLFW window to fullscreen mode using the resolution
   * and refresh rate of the primary monitor. The function also updates the width and height
   * variables to reflect the new resolution.
   *
   * @param window A shared pointer to the GLFW window object.
   * @param width A reference to an integer that will store the window's width.
   * @param height A reference to an integer that will store the window's height.
   */
  void setFullScreen(std::shared_ptr<GLFWwindow> &window, int &width, int &height);

  /**
   * @brief Switch a window to windowed mode.
   *
   * This function sets the specified GLFW window to windowed mode and restores its size
   * to the provided dimensions. The window will also be placed at a default position
   * (top-left corner) or can be manually adjusted later.
   *
   * @param window A shared pointer to the GLFW window object.
   * @param width The desired width of the window.
   * @param height The desired height of the window.
   */
  void setWindowed(std::shared_ptr<GLFWwindow> &window, int &width, int &height);
} // namespace Utils

#endif // UTILS_GRAPHICSUTILS_HPP_
