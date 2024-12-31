#include "Core/Application.hpp"

void frame_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

namespace Core
{

  Application::Application() : window(nullptr), is_running(true), keyboard{nullptr}
  {
  }

  Application::~Application()
  {
    if (window)
    {
      glfwDestroyWindow(window);
    }

    glfwTerminate();
  }

  /// @brief Initializes the application.
  ///
  /// Sets up the GLFW window, OpenGL context, and input handling.
  ///
  /// @param WIDTH The width of the application window.
  /// @param HEIGHT The height of the application window.
  void Application::Initialize(int WIDTH, int HEIGHT)
  {
    if (!glfwInit())
    {
      spdlog::error("GLFW initialization failed");
      return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "AtmosphEX", nullptr, nullptr);

    if (window == nullptr)
    {
      spdlog::error("ERROR::APPLICATION::Could not create the window");
      glfwTerminate();
      is_running = false;
      return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      spdlog::error("ERROR::APPLICATION::Failed to initialize GLAD");

      return;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, frame_callback);

    spdlog::info("SUCCESS::APPLICATION::Application Initialized!");
  }

  /// @brief Runs the main application loop.
  ///
  /// Handles delta time calculations, rendering, updating, and event polling.
  void Application::Run()
  {
    float current_frame;
    float last_frame = glfwGetTime();
    float delta_time;

    Start();
    while (!glfwWindowShouldClose(window))
    {
      // Delta time
      current_frame = glfwGetTime();
      delta_time = current_frame - last_frame;
      last_frame = current_frame;

      Render();
      Update(delta_time);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  /// @brief Renders the application scene.
  ///
  /// Clears the color buffer and draws graphics objects.
  void Application::Render()
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    meshes["test"]->Draw();
  }

  /// @brief Updates the application state every frame.
  ///
  /// Handles input and updates game logic.
  ///
  /// @param deltaTime The time elapsed since the last frame, in seconds.
  void Application::Update(float &deltaTime)
  {
    // TODO: Move this ha
    // Keyboard
    std::function<void()> close_window_action = [this]
    {
      glfwSetWindowShouldClose(this->window, true);
    };

    keyboard->IsKeyDown(GLFW_KEY_ESCAPE, close_window_action);

    // Physics
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Model
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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

  /// @brief Performs setup tasks before the main loop starts.
  ///
  /// Prepares shaders, resources, and other dependencies.
  void Application::Start()
  {
    // glEnable(GL_CULL_FACE); // Enable face culling
    // glCullFace(GL_BACK);    // Cull back faces
    // glFrontFace(GL_CCW);    // Define counter-clockwise winding as front-facing

    keyboard = std::make_shared<Input::Keyboard>(window);
    if (keyboard == nullptr)
    {
      spdlog::error("ERROR::APPLICATION::Could not Initialized the Keyboard");
      return;
    }

    camera = std::make_unique<Utils::Camera>(keyboard);

    shaders["Default"] = std::make_unique<Graphics::Shader>("../res/shaders/cube/cube.vert", "../res/shaders/cube/cube.frag");
    shaders["Default"]->Use();

    meshes["test"] = std::make_unique<Graphics::Mesh>();
    meshes["test"]->Load("../res/models/saturn_v_-_nasa.glb");
  }

}
