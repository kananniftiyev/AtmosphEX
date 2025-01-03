#include "UI/ImguiManager.hpp"

namespace UI
{
  ImguiManager::ImguiManager(std::shared_ptr<GLFWwindow> window)
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
  }

  ImguiManager::~ImguiManager()
  {
    ImGui::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
  }

  void ImguiManager::Stats(StatsData &stat)
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen))
    {
      // Content inside the group when expanded
      ImGui::Text("Scene Name: %s", stat.scene_name.c_str());
      ImGui::Text("FPS: %d", stat.fps);
      ImGui::Text("Memory Usage: %d", stat.memory_usage);
      ImGui::Text("CPU Usage: %f", stat.cpu_usage);
      ImGui::Text("GPU Load: %d", stat.gpu_load);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
} // namespace UI
