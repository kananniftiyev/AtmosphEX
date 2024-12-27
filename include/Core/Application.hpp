#ifndef CORE_APPLICATION_HPP_
#define CORE_APPLICATION_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include <stdexcept>

#include "Input/Keyboard.hpp"

namespace Core
{
  class Application
  {
  private:
    GLFWwindow *window;
    bool is_running;

    void Render();
    void Update(float deltaTime);

  public:
    Application(/* args */);
    ~Application(/* args */);

    void Run();
    void Initialize(int WIDTH, int HEIGHT);
  };
}

#endif // CORE_APPLICATION_HPP_