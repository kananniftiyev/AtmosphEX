#ifndef UI_IMGUIMANAGER_HPP_
#define UI_IMGUIMANAGER_HPP_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <memory>
#include <iostream>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace UI
{
  class ImguiManager
  {
  private:
    /* data */
  public:
    struct Data
    {
      std::string scene_name;
      int fps;
      long int memory_usage;
      float cpu_usage;
      int gpu_load;
      glm::vec3 camera_position;
      glm::vec3 camera_rotation;
    };

    ImguiManager(std::shared_ptr<GLFWwindow> window);
    ~ImguiManager();

    void stats(Data &stat);
    void windowControl(std::function<void()> fullScreen, std::function<void()> windowed);
    void render();
    void newFrame();
  };

} // namespace UI

#endif // UI_IMGUIMANAGER_HPP_