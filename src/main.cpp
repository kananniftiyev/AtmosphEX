#include <iostream>
#include <exception>

#include "Core/Application.hpp"

int main(int argc, char *argv[])
{
  Core::Application app;
  // TODO: exceptions
  app.Initialize(800, 600);
  app.Run();
  return 0;
}
