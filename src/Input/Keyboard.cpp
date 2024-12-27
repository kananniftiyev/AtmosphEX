#include "Input/Keyboard.hpp"

namespace Input
{
  Keyboard::Keyboard(GLFWwindow *window) : window{window} {}

  Keyboard::~Keyboard() {}

  void Keyboard::IsKeyDown(int key, std::function<void()> func)
  {
    if (glfwGetKey(window, key) == GLFW_PRESS)
    {
      func();
    }
  }

  void Keyboard::IsKeyHeld(int key, std::function<void()> func)
  {
    if (glfwGetKey(window, key) == GLFW_REPEAT)
    {
      func();
    }
  }

  void Keyboard::IsKeyReleased(int key, std::function<void()> func)
  {
    if (glfwGetKey(window, key) == GLFW_RELEASE)
    {
      func();
    }
  }
}