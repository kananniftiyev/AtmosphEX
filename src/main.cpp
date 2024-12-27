#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Application.hpp"

void process(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
  }
}

int main()
{
  Core::Application app;

  app.Initialize(800, 600);
  app.Run();
  return 0;
}
