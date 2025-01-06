#ifndef INPUT_KEYBOARD_HPP_
#define INPUT_KEYBOARD_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <functional>

namespace Input
{
  class Keyboard
  {
  private:
    std::shared_ptr<GLFWwindow> window;
    std::unordered_map<char, int> key_map;

    // void loadJsonMap();

  public:
    Keyboard(std::shared_ptr<GLFWwindow> &w);
    ~Keyboard();

    bool isKeyDown(const int &key);
    bool isKeyHeld(const int &key);
    bool isKeyReleased(const int &key);
    std::unordered_map<char, int> getKeyMap() const;
  };

}

#endif // INPUT_KEYBOARD_HPP_