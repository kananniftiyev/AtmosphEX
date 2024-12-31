#include <iostream>
#include <exception>

#include "Core/Application.hpp"

int main()
{
  Core::Application app;

  app.Initialize(800, 600);
  app.Run();
  return 0;
}
