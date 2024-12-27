#ifndef INPUT_KEYBOARD_HPP_
#define INPUT_KEYBOARD_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>

namespace Input
{
  class Keyboard
  {
  private:
    GLFWwindow *window;

  public:
    Keyboard(GLFWwindow *window);
    ~Keyboard();

    void IsKeyDown(int key, std::function<void()> &func);
    void IsKeyHeld(int key, std::function<void()> &func);
    void IsKeyReleased(int key, std::function<void()> &func);
  };

}

#endif // INPUT_KEYBOARD_HPP_