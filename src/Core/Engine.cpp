#include "Core/Engine.hpp"

namespace Core
{

  // Settings

  void Engine::actions(float &deltaTime)
  {
    for (auto key : keyboard->getKeyMap())
    {
      if (keyboard->isKeyDown(key.second))
      {
        switch (key.first)
        {
        case 'w':
          camera->move(deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
          break;
        case 'a':
          camera->move(deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
          break;
        case 's':
          camera->move(deltaTime, glm::vec3(0.0f, 0.0f, -1.0f));
          break;
        case 'd':
          camera->move(deltaTime, glm::vec3(-1.0f, 0.0f, 0.0f));
          break;

        default:
          break;
        }
      }
    }
  }

  // Main
  Engine::Engine(std::shared_ptr<GLFWwindow> &w, int width, int height) : window{w}, m_width{width}, m_height{height}
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

    delete camera;
  };

  void Engine::start()
  {
    // Init Components
    camera = Graphics::Camera::new_camera(glm::vec3(0.0f, 0.0f, -10.0f), 5);
    keyboard = std::make_shared<Input::Keyboard>(window);
    imgui = std::make_unique<UI::ImguiManager>(window);
    // Logic
    if (keyboard == nullptr)
    {
      spdlog::error("ERROR::APPLICATION::Could not Initialized the Keyboard");
      return;
    }

    shaders["Default"] = std::make_shared<Graphics::Shader>("./res/shaders/cube/cube-ver.glsl", "./res/shaders/cube/cube-frag.glsl");
    shaders["Default"]->use();

    models["skull"] = std::make_unique<Graphics::Model>("./res/models/12140_Skull_v3_L2.obj", "./res/models/");

    glfwSwapInterval(1);
  }

  void Engine::render()
  {

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
  }

  void Engine::update(float &deltaTime)
  {

    // Keyboard
    if (keyboard->isKeyDown(GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(window.get(), true);
    }

    actions(deltaTime);

    // Physics
    glm::mat4 projection = glm::mat4(1.0f);

    // Model
    models["skull"]->rotateObject(1.0f, 0.0f, 0.0f, glm::radians(-90.0f));
    models["skull"]->scaleObject(0.2f, 0.2f, 0.2f);
    models["skull"]->apply(shaders["Default"]);
    // Camera

    // Ortho/Perspective, FOV, Aspect Ratio
    glfwGetWindowSize(window.get(), &m_width, &m_height);
    projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);

    shaders["Default"]->setMat4("view", camera->getViewMatrix());
    shaders["Default"]->setMat4("projection", projection);
    shaders["Default"]->setVec3("objectColor", 1.0f, 0.5f, 0.31f); // Example orange-like object color
    shaders["Default"]->setVec3("lightColor", 1.0f, 1.0f, 1.0f);   // White light
    shaders["Default"]->setVec3("lightPos", 1.2f, 1.0f, 2.0f);     // Light position in the scene
    shaders["Default"]->setVec3("viewPos", 0.0f, 0.0f, -5.0f);     // Camera position

    // Imgui
    UI::ImguiManager::Data stat;
    stat.scene_name = "Test";
    stat.fps = static_cast<int>(1.0f / deltaTime);
    stat.memory_usage = Utils::get_mem_usage();
    stat.camera_position = camera->getPosition();
    stat.camera_rotation = camera->getRotation();

    imgui->newFrame();
    imgui->stats(stat);
    imgui->windowControl([this]
                         { Utils::setFullScreen(window, this->m_width, this->m_height); }, [this]
                         { Utils::setWindowed(window, this->m_width, this->m_height); });

    imgui->render();
  }

} // namespace Core
