#ifndef INPUT_KEYBOARD_HPP_
#define INPUT_KEYBOARD_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <memory>

namespace Input
{
  class Keyboard
  {
  private:
    std::shared_ptr<GLFWwindow> window;

  public:
    Keyboard(std::shared_ptr<GLFWwindow> w);
    ~Keyboard();

    void IsKeyDown(const int &key, std::function<void()> &func);
    void IsKeyHeld(const int &key, std::function<void()> &func);
    void IsKeyReleased(const int &key, std::function<void()> &func);
  };

}

#endif // INPUT_KEYBOARD_HPP_