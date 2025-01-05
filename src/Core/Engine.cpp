#include "Core/Engine.hpp"
using Clock = std::chrono::high_resolution_clock;

namespace Core
{

  // Settings
  void Engine::setFullScreen()
  {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    // Get the video mode of the monitor (resolution)
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwGetWindowSize(window.get(), &m_width, &m_height);

    // Make the window fullscreen by setting it to the monitor's resolution
    glfwSetWindowMonitor(window.get(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

    m_width = mode->width;
    m_height = mode->height;
  }

  void Engine::setWindowed()
  {
    m_width = 800;
    m_height = 600;
    glfwSetWindowMonitor(window.get(), nullptr, 0, 0, m_width, m_height, 0);
  }

  // Main
  Engine::Engine(std::shared_ptr<GLFWwindow> w, int width, int height) : window{w}, m_width{width}, m_height{height}
  {
  }

  Engine::~Engine()
  {
    // Shutdown ImGui
    ImGui_ImplOpenGL3_Shutdown(); // For the OpenGL renderer
    ImGui_ImplGlfw_Shutdown();    // For the GLFW platform backend
    ImGui::DestroyContext();      // Destroys the ImGui context

    // Terminate GLFW
    glfwDestroyWindow(window.get()); // Destroy the window
    glfwTerminate();                 // Terminate the GLFW library
  };

  void Engine::start()
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
    shaders["Default"]->use();

    std::thread load([this]
                     { models["skull"] = std::make_unique<Graphics::Model>("./res/models/12140_Skull_v3_L2.obj", "./res/models/"); });

    load.join();

    // glfwSwapInterval(0);
  }

  void Engine::render()
  {
    glGenQueries(1, &query);
    glBeginQuery(GL_TIME_ELAPSED, query);

    if (models["skull"]->is_model_loaded && !models["skull"]->is_model_ready)
    {
      models["skull"]->setupObj();
    }

    if (models.find("skull") != models.end())
    {

      models["skull"]->draw();
    }
    else
    {
      spdlog::warn("Model not loaded yet!");
    }

    glEndQuery(GL_TIME_ELAPSED);
  }

  void Engine::update(float &deltaTime)
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
    models["skull"]->rotateObject(1.0f, 0.0f, 0.0f, glm::radians(-90.0f));
    models["skull"]->scaleObject(0.2f, 0.2f, 0.2f);
    models["skull"]->apply(shaders["Default"]);
    // Camera
    camera->MoveAround(deltaTime);
    //  Ortho/Perspective, FOV, Aspect Ratio
    glfwGetWindowSize(window.get(), &m_width, &m_height);
    projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);

    shaders["Default"]->setMat4("view", camera->GetPosition());
    shaders["Default"]->setMat4("projection", projection);
    shaders["Default"]->setVec3("objectColor", 1.0f, 0.5f, 0.31f); // Example orange-like object color
    shaders["Default"]->setVec3("lightColor", 1.0f, 1.0f, 1.0f);   // White light
    shaders["Default"]->setVec3("lightPos", 1.2f, 1.0f, 2.0f);     // Light position in the scene
    shaders["Default"]->setVec3("viewPos", 0.0f, 0.0f, -5.0f);     // Camera position

    GLuint64 elapsedTime;
    glGetQueryObjectui64v(query, GL_QUERY_RESULT, &elapsedTime);

    // Imgui
    UI::ImguiManager::StatsData stat;
    stat.scene_name = "Test";
    stat.fps = static_cast<int>(1.0f / deltaTime);
    stat.cpu_usage = 5;
    stat.memory_usage = 66;
    stat.gpu_load = elapsedTime;

    imgui->newFrame();
    imgui->stats(stat);
    imgui->windowControl([this]
                         { setFullScreen(); }, [this]
                         { setWindowed(); });

    imgui->render();
  }

} // namespace Core
