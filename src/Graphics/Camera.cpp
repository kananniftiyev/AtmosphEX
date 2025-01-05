#include "Graphics/Camera.hpp"

namespace Graphics
{
  Camera::Camera(glm::vec3 position, float sensitivity) : m_position{position}, m_rotation{glm::vec3(0.0f)}, m_view{glm::mat4(1.0f)}, m_sensitivity{sensitivity}
  {
    m_view = glm::translate(m_view, position);
    m_position = glm::vec3(m_view[3][0], m_view[3][1], m_view[3][2]);
  }

  Camera::~Camera() {}

  Camera *Camera::m_camera = nullptr;
  Camera *Camera::make_camera(glm::vec3 position, float sensitivity)
  {
    if (m_camera == nullptr)
    {
      m_camera = new Camera(position, sensitivity);
    }

    return m_camera;
  }

  // Actions
  void Camera::move(float &deltaTime, const glm::vec3 &direction)
  {
    m_view = glm::translate(m_view, direction * deltaTime * m_sensitivity);
    m_position = glm::vec3(m_view[3][0], m_view[3][1], m_view[3][2]);
  }

  void Camera::rotate(float &deltaTime, const float angle, const glm::vec3 &axis)
  {
    m_view = glm::rotate(m_view, glm::radians(angle), axis);
    glm::mat3 rotationMatrix = glm::mat3(m_view);
    m_rotation = glm::eulerAngles(glm::quat_cast(rotationMatrix));
  }

  void Camera::lookAt(glm::vec3 target)
  {
    m_view = glm::lookAt(m_position, target, glm::vec3(0.0f, 1.0f, 0.0f));
  }

  // Properties
  glm::mat4 Camera::getViewMatrix() const
  {
    return m_view;
  }

  glm::vec3 Camera::getPosition() const { return m_position; }
  glm::vec3 Camera::getRotation() const { return m_rotation; }

} // namespace Utils
