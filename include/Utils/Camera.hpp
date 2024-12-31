#ifndef GRAPHICS_CAMERA_HPP_
#define GRAPHICS_CAMERA_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input/Keyboard.hpp"

namespace Utils
{
  class Camera
  {
  private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 view;
    float sensitivity;
    std::shared_ptr<Input::Keyboard> keyboard;

  public:
    Camera(std::shared_ptr<Input::Keyboard> kb, float sensitivity = 10);
    ~Camera();
    void MoveAround(float deltaTime);
    glm::mat4 GetPosition();
  };

} // namespace Graphics

#endif // GRAPHICS_CAMERA_HPP_