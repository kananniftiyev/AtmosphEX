#ifndef CORE_APPLICATION_HPP_
#define CORE_APPLICATION_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <memory>
#include <spdlog/spdlog.h>
#include <vector>
#include <unordered_map>
#include <filesystem>

#include "Core/Engine.hpp"

namespace Core
{
  class Application
  {
  private:
    std::shared_ptr<GLFWwindow> window;
    std::unique_ptr<Engine> engine;

    // properties
    bool is_running;

  public:
    Application();
    ~Application();

    /// @brief Runs the main application loop.
    ///
    /// Handles delta time calculations, rendering, updating, and event polling.
    void run();

    /// @brief Initializes the application.
    ///
    /// Sets up the GLFW window, OpenGL context, and input handling.
    ///
    /// @param WIDTH The width of the application window.
    /// @param HEIGHT The height of the application window.
    void initialize(int &WIDTH, int &HEIGHT);
  };
}

#endif // CORE_APPLICATION_HPP_