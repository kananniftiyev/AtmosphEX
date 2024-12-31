#include "Utils/Camera.hpp"

namespace Utils
{
  Camera::Camera(std::shared_ptr<Input::Keyboard> kb, float sensitivity) : keyboard(kb), position{glm::vec3(0.0f)}, rotation{glm::vec3(0.0f)}, view{glm::mat4(1.0f)}, sensitivity{sensitivity}
  {
  }

  Camera::~Camera() {}

  void Camera::MoveAround(float deltaTime)
  {
    std::function<void()> move_forward = [this, deltaTime]
    {
      this->view = glm::translate(view, glm::vec3(0.0f, 0.0f, 1.0f) * deltaTime * this->sensitivity);
    };
    std::function<void()> move_left = [this, deltaTime]
    {
      this->view = glm::translate(view, glm::vec3(1.0f, 0.0f, 0.0f) * deltaTime * this->sensitivity);
    };
    std::function<void()> move_right = [this, deltaTime]
    {
      this->view = glm::translate(view, glm::vec3(-1.0f, 0.0f, 0.0f) * deltaTime * this->sensitivity);
    };
    std::function<void()> move_backwards = [this, deltaTime]
    {
      this->view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f) * deltaTime * this->sensitivity);
    };
    std::function<void()> move_up = [this, deltaTime]
    {
      this->view = glm::translate(view, glm::vec3(0.0f, -1.0f, 0.0f) * deltaTime * this->sensitivity);
    };
    std::function<void()> move_down = [this, deltaTime]
    {
      this->view = glm::translate(view, glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * this->sensitivity);
    };

    position = glm::vec3(view[3][0], view[3][1], view[3][2]);
    spdlog::info("x: {} y: {} z:{}", position.x, position.y, position.z);

    keyboard->IsKeyDown(GLFW_KEY_W, move_forward);
    keyboard->IsKeyDown(GLFW_KEY_A, move_left);
    keyboard->IsKeyDown(GLFW_KEY_S, move_backwards);
    keyboard->IsKeyDown(GLFW_KEY_D, move_right);
    keyboard->IsKeyDown(GLFW_KEY_SPACE, move_up);
    keyboard->IsKeyDown(GLFW_KEY_LEFT_SHIFT, move_down);
  }

  glm::mat4 Camera::GetPosition()
  {
    return view;
  }
} // namespace Utils
