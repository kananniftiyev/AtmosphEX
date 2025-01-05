#ifndef CORE_ENGINE_HPP_
#define CORE_ENGINE_HPP_

#include "UI/ImguiManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <memory>
#include <vector>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <unistd.h>

#include "Graphics/Cube.hpp"
#include "Graphics/Shader.hpp"
#include "Input/Keyboard.hpp"
#include "Graphics/Model.hpp"
#include "Utils/Camera.hpp"

namespace Core
{
  class Engine
  {
  private:
    GLuint query;
    // Components
    std::shared_ptr<GLFWwindow> window;
    std::shared_ptr<Input::Keyboard> keyboard;
    std::unique_ptr<Utils::Camera> camera;
    std::unique_ptr<UI::ImguiManager> imgui;

    std::unordered_map<std::string, std::unique_ptr<Graphics::Model>>
        models;
    std::unordered_map<std::string, std::shared_ptr<Graphics::Shader>> shaders;

    // Properties
    int m_width;
    int m_height;

    // Helper Funcs
    void setFullScreen();
    void setWindowed();

  public:
    Engine(std::shared_ptr<GLFWwindow> w, int width, int height);
    ~Engine();

    /// @brief Performs setup tasks before the main loop starts.
    ///
    /// Prepares shaders, resources, and other dependencies.
    void start();

    /// @brief Updates the application state every frame.
    ///
    /// Handles input and updates game logic.
    ///
    /// @param deltaTime The time elapsed since the last frame, in seconds.
    void update(float &deltaTime);

    /// @brief Renders the application scene.
    ///
    /// Clears the color buffer and draws graphics objects.
    void render();

    // Settings
  };

} // namespace Core

#endif // CORE_ENGINE_HPP_