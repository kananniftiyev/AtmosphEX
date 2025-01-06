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

namespace Graphics
{
  class Camera
  {
  private:
    // Properties
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::mat4 m_view;
    float m_sensitivity;

    // Singleton
    static Camera *m_camera;

  public:
    Camera(glm::vec3 position = glm::vec3(0.0f), float sensitivity = 10);
    Camera(Camera &other) = delete;
    void operator=(const Camera &) = delete;

    static Camera *new_camera(glm::vec3 position, float sensitivity);

    // Actions
    void move(float &deltaTime, const glm::vec3 &direction);
    void rotate(float &deltaTime, const float &angle, const glm::vec3 &axis);
    void lookAt(glm::vec3 &target);

    // Properties
    glm::mat4
    getViewMatrix() const;
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
  };

} // namespace Graphics

#endif // GRAPHICS_CAMERA_HPP_