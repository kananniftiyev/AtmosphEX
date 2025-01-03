#ifndef UI_IMGUIMANAGER_HPP_
#define UI_IMGUIMANAGER_HPP_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <memory>
#include <iostream>

namespace UI
{
  class ImguiManager
  {
  private:
    /* data */
  public:
    struct StatsData
    {
      std::string scene_name;
      int fps;
      long int memory_usage;
      float cpu_usage;
      int gpu_load;
    };

    ImguiManager(std::shared_ptr<GLFWwindow> window);
    ~ImguiManager();

    void Stats(StatsData &stat);
  };

} // namespace UI

#endif // UI_IMGUIMANAGER_HPP_