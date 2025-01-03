#include "Input/Keyboard.hpp"

namespace Input
{
  Keyboard::Keyboard(std::shared_ptr<GLFWwindow> w) : window{w} {}

  Keyboard::~Keyboard() {}

  void Keyboard::IsKeyDown(const int &key, std::function<void()> &func)
  {
    if (glfwGetKey(window.get(), key) == GLFW_PRESS)
    {
      func();
    }
  }

  void Keyboard::IsKeyHeld(const int &key, std::function<void()> &func)
  {
    if (glfwGetKey(window.get(), key) == GLFW_REPEAT)
    {
      func();
    }
  }

  void Keyboard::IsKeyReleased(const int &key, std::function<void()> &func)
  {
    if (glfwGetKey(window.get(), key) == GLFW_RELEASE)
    {
      func();
    }
  }
}