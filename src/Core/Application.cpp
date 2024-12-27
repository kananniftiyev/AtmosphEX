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
    glfwTerminate();
  }

  void Application::Run()
  {
    float current_frame;
    float last_frame = glfwGetTime();
    float delta_time;

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
      spdlog::error("Could not create the window");
      glfwTerminate();
      is_running = false;
      return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      spdlog::error("Failed to initialize GLAD");

      return;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, frame_callback);

    keyboard = std::make_unique<Input::Keyboard>(window);
    if (keyboard == nullptr)
    {
      spdlog::error("Could not Initialized the Keyboard");
      return;
    }
    spdlog::info("Application Initialized!");
  }

  void Application::Render()
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Application::Update(float deltaTime)
  {
    std::function<void()> close_window_action = [this]
    {
      glfwSetWindowShouldClose(this->window, true);
    };

    keyboard->IsKeyDown(GLFW_KEY_ESCAPE, close_window_action);
  }

}
