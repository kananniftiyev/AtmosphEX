#include "Core/Application.hpp"

void frame_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

namespace Core
{

  Application::Application() : window(nullptr), is_running(true)
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
      std::cerr << "GLFW initialization failed" << std::endl;
      return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "AtmosphEX", nullptr, nullptr);

    if (window == nullptr)
    {
      std::cerr << "Could not create the window" << std::endl;
      glfwTerminate();
      is_running = false;
      return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, frame_callback);

    std::cout << "Application Initialized!" << std::endl;
  }

  void Application::Render()
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Application::Update(float deltaTime)
  {
    Input::Keyboard keyboard(window);
    keyboard.IsKeyDown(GLFW_KEY_ESCAPE, [this]
                       { glfwSetWindowShouldClose(this->window, true); });
  }

}
