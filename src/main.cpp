#include <iostream>
#include <exception>

#include "Core/Application.hpp"

int main(int argc, char *argv[])
{
  int app_width = 800;
  int app_height = 600;

  Core::Application app;
  // TODO: exceptions
  app.initialize(app_width, app_height);
  app.run();
  return 0;
}
