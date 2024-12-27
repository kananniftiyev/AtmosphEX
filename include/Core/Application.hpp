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

#include <Graphics/Cube.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Mesh.hpp>
#include "Input/Keyboard.hpp"

namespace Core
{
  class Application
  {
  private:
    GLFWwindow *window;
    std::unique_ptr<Input::Keyboard> keyboard;

    std::vector<Graphics::Mesh> meshes;
    bool is_running;

    void Render();
    void Update(float deltaTime);
    void Start() const;

  public:
    Application(/* args */);
    ~Application(/* args */);

    void Run();
    void Initialize(int WIDTH, int HEIGHT);
  };
}

#endif // CORE_APPLICATION_HPP_