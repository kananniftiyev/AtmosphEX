#include "Input/Keyboard.hpp"

namespace Input
{
  Keyboard::Keyboard(std::shared_ptr<GLFWwindow> w) : window{w}
  {
    key_map['w'] = GLFW_KEY_W;
    key_map['a'] = GLFW_KEY_A;
    key_map['s'] = GLFW_KEY_S;
    key_map['d'] = GLFW_KEY_D;
    key_map['l'] = GLFW_KEY_LEFT_CONTROL;
    key_map['z'] = GLFW_KEY_LEFT_SHIFT;
  }

  Keyboard::~Keyboard() {}

  bool Keyboard::isKeyDown(const int &key)
  {
    if (glfwGetKey(window.get(), key) == GLFW_PRESS)
    {
      return true;
    }
    return false;
  }

  bool Keyboard::isKeyHeld(const int &key)
  {
    if (glfwGetKey(window.get(), key) == GLFW_REPEAT)
    {
      return true;
    }
    return false;
  }

  bool Keyboard::isKeyReleased(const int &key)
  {
    if (glfwGetKey(window.get(), key) == GLFW_RELEASE)
    {
      return true;
    }
    return false;
  }

  std::unordered_map<char, int> Keyboard::getKeyMap() const
  {
    return key_map;
  }
}