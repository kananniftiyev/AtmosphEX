#include "Core/Application.hpp"

void frame_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

namespace Core
{

  Application::Application() : window(nullptr), is_running(true)
  {
    std::cout << std::filesystem::current_path() << std::endl;
  }

  Application::~Application()
  {
    if (window)
    {
      glfwDestroyWindow(window.get());
    }

    glfwTerminate();
  }

  void Application::initialize(int &WIDTH, int &HEIGHT)
  {
    if (!glfwInit())
    {
      spdlog::error("GLFW initialization failed");
      return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Custom deleter for GLFWwindow
    struct GLFWwindowDeleter
    {
      void operator()(GLFWwindow *win) const
      {
        if (win)
        {
          glfwDestroyWindow(win);
        }
      }
    };

    window = std::shared_ptr<GLFWwindow>(
        glfwCreateWindow(WIDTH, HEIGHT, "AtmosphEX", nullptr, nullptr), GLFWwindowDeleter());

    engine = std::make_unique<Core::Engine>(window, WIDTH, HEIGHT);

    if (window == nullptr)
    {
      spdlog::error("ERROR::APPLICATION::Could not create the window");
      glfwTerminate();
      is_running = false;
      return;
    }

    glfwMakeContextCurrent(window.get());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      spdlog::error("ERROR::APPLICATION::Failed to initialize GLAD");

      return;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window.get(), frame_callback);

    spdlog::info("SUCCESS::APPLICATION::Application Initialized!");
  }

  void Application::run()
  {
    float current_frame;
    float last_frame = glfwGetTime();
    float delta_time;

    engine->start();
    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window.get()))
    {
      glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Delta time
      current_frame = glfwGetTime();
      delta_time = current_frame - last_frame;
      last_frame = current_frame;

      engine->render();
      engine->update(delta_time);

      glFinish();
      glfwSwapBuffers(window.get());
      glfwPollEvents();
    }
  }

}
