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

  void ImguiManager::Stats(StatsData &stat)
  {
    ImGui::Begin("Stats", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen))
    {
      ImGui::Text("Scene Name: %s", stat.scene_name.c_str());
      ImGui::Text("FPS: %d", stat.fps);
      ImGui::Text("Memory Usage: %d", stat.memory_usage);
      ImGui::Text("CPU Usage: %f", stat.cpu_usage);
      ImGui::Text("GPU Load: %d", stat.gpu_load);
    }

    ImGui::End();
  }

  void ImguiManager::WindowControl(std::function<void()> fullScreen, std::function<void()> windowed)
  {
    ImGui::Begin("Window Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::Button("Fullscreen"))
    {
      fullScreen();
    }
    ImGui::SameLine();
    if (ImGui::Button("Windowed"))
    {
      windowed();
    }

    ImGui::End();
  }

  void ImguiManager::Render()
  {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImguiManager::NewFrame()
  {
    // Call this once per frame to initialize ImGui for the current frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }
} // namespace UI
