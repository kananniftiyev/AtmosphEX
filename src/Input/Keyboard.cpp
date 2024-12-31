#include "Input/Keyboard.hpp"

namespace Input
{
  Keyboard::Keyboard(std::shared_ptr<GLFWwindow> w) : window{w} {}

  Keyboard::~Keyboard() {}

  void Keyboard::IsKeyDown(int key, std::function<void()> &func)
  {
    if (glfwGetKey(window.get(), key) == GLFW_PRESS)
    {
      func();
    }
  }

  void Keyboard::IsKeyHeld(int key, std::function<void()> &func)
  {
    if (glfwGetKey(window.get(), key) == GLFW_REPEAT)
    {
      func();
    }
  }

  void Keyboard::IsKeyReleased(int key, std::function<void()> &func)
  {
    if (glfwGetKey(window.get(), key) == GLFW_RELEASE)
    {
      func();
    }
  }
}