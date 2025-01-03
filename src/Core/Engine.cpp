#include "Core/Engine.hpp"
using Clock = std::chrono::high_resolution_clock;

namespace Core
{
  Engine::Engine(std::shared_ptr<GLFWwindow> w) : window{w}
  {
  }

  Engine::~Engine() {};

  void Engine::Start()
  {

    imgui = std::make_unique<UI::ImguiManager>(window);

    keyboard = std::make_shared<Input::Keyboard>(window);
    if (keyboard == nullptr)
    {
      spdlog::error("ERROR::APPLICATION::Could not Initialized the Keyboard");
      return;
    }

    camera = std::make_unique<Utils::Camera>(keyboard);

    shaders["Default"] = std::make_shared<Graphics::Shader>("./res/shaders/cube/cube-ver.glsl", "./res/shaders/cube/cube-frag.glsl");
    shaders["Default"]->Use();

    std::thread load([this]
                     { models["skull"] = std::make_unique<Graphics::Model>("./res/models/12140_Skull_v3_L2.obj", "./res/models/"); });

    load.join();

    // glfwSwapInterval(0);
  }

  void Engine::Render()
  {
    glGenQueries(1, &query);
    glBeginQuery(GL_TIME_ELAPSED, query);

    if (models["skull"]->isModelLoaded && !models["skull"]->isMeshReady)
    {
      models["skull"]->setupObj();
    }

    if (models.find("skull") != models.end())
    {

      models["skull"]->Draw();
    }
    else
    {
      spdlog::warn("Model not loaded yet!");
    }

    glEndQuery(GL_TIME_ELAPSED);
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
    glm::mat4 projection = glm::mat4(1.0f);

    // Model
    models["skull"]->RotateObject(1.0f, 0.0f, 0.0f, glm::radians(-90.0f));
    models["skull"]->ScaleObject(0.2f, 0.2f, 0.2f);
    models["skull"]->Apply(shaders["Default"]);
    // Camera
    camera->MoveAround(deltaTime);
    //  Ortho/Perspective, FOV, Aspect Ratio
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shaders["Default"]->SetMat4("view", camera->GetPosition());
    shaders["Default"]->SetMat4("projection", projection);
    shaders["Default"]->SetVec3("objectColor", 1.0f, 0.5f, 0.31f); // Example orange-like object color
    shaders["Default"]->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);   // White light
    shaders["Default"]->SetVec3("lightPos", 1.2f, 1.0f, 2.0f);     // Light position in the scene
    shaders["Default"]->SetVec3("viewPos", 0.0f, 0.0f, -5.0f);     // Camera position

    GLuint64 elapsedTime;
    glGetQueryObjectui64v(query, GL_QUERY_RESULT, &elapsedTime);

    // Imgui
    UI::ImguiManager::StatsData stat;
    stat.scene_name = "Test";
    stat.fps = static_cast<int>(1.0f / deltaTime);
    stat.cpu_usage = 5;
    stat.memory_usage = 66;
    stat.gpu_load = elapsedTime;
    imgui->Stats(stat);
  }
} // namespace Core
