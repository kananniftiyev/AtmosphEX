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

#include <Graphics/Cube.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Mesh.hpp>
#include "Input/Keyboard.hpp"
#include "Graphics/Mesh.hpp"
#include "Utils/Camera.hpp"

namespace Core
{
  class Application
  {
  private:
    GLFWwindow *window;
    std::shared_ptr<Input::Keyboard> keyboard;
    std::unique_ptr<Utils::Camera> camera;

    std::unordered_map<std::string, std::unique_ptr<Graphics::Mesh>> meshes;
    std::unordered_map<std::string, std::unique_ptr<Graphics::Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<Graphics::Cube>> cubes;

    bool is_running;

    void Render();
    void Update(float &deltaTime);
    void Start();

    struct RenderObject
    {
      std::string shader_name;
      std::string mesh_name;
    };

    std::vector<RenderObject> render_queue;

  public:
    Application();
    ~Application();

    void Run();
    void Initialize(int WIDTH, int HEIGHT);
  };
}

#endif // CORE_APPLICATION_HPP_