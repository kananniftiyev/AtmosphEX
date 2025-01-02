#include "Core/Engine.hpp"

namespace Core
{
  Engine::Engine(std::shared_ptr<GLFWwindow> w) : window{w}
  {
  }

  Engine::~Engine() {};

  void Engine::Start()
  {
    keyboard = std::make_shared<Input::Keyboard>(window);
    if (keyboard == nullptr)
    {
      spdlog::error("ERROR::APPLICATION::Could not Initialized the Keyboard");
      return;
    }

    camera = std::make_unique<Utils::Camera>(keyboard);

    shaders["Default"] = std::make_shared<Graphics::Shader>("./res/shaders/cube/cube.vert", "./res/shaders/cube/cube.frag");
    shaders["Default"]->Use();

    models["skull"] = std::make_unique<Graphics::Model>("./res/models/12140_Skull_v3_L2.obj", "./res/models/");

    glfwSwapInterval(1);
  }

  void Engine::Render()
  {
    models["skull"]->Draw();
  }

  void Engine::Update(float &deltaTime)
  {
    // TODO: Move this ha
    // Keyboard
    std::function<void()> close_window_action = [this]
    {
      glfwSetWindowShouldClose(this->window.get(), true);
    };

    keyboard->IsKeyDown(GLFW_KEY_ESCAPE, close_window_action);

    // Physics
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Model
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // Camera
    camera->MoveAround(deltaTime);
    // view = glm::rotate(view, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //  Ortho/Perspective, FOV, Aspect Ratio
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shaders["Default"]->SetMat4("model", model);
    shaders["Default"]->SetMat4("view", camera->GetPosition());
    shaders["Default"]->SetMat4("projection", projection);
    shaders["Default"]->SetVec3("objectColor", 1.0f, 0.5f, 0.31f); // Example orange-like object color
    shaders["Default"]->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);   // White light
    shaders["Default"]->SetVec3("lightPos", 1.2f, 1.0f, 2.0f);     // Light position in the scene
    shaders["Default"]->SetVec3("viewPos", 0.0f, 0.0f, -5.0f);     // Camera position
  }
} // namespace Core
