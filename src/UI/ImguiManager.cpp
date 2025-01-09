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
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();
  }

  void ImguiManager::stats(Data &stat)
  {
    ImGui::Begin("Stats", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen))
    {
      ImGui::Text("Scene Name: %s", stat.scene_name.c_str());
      ImGui::Text("FPS: %d", stat.fps);
      ImGui::Text("Max Memory Usage: %.2f MB", stat.memory_usage / 1024.0);
    }

    if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
    {
      ImGui::Text("Camera Position: x: %.2f, y: %.2f, z: %.2f",
                  stat.camera_position.x,
                  stat.camera_position.y,
                  stat.camera_position.z);
      ImGui::Text("Camera Position: x: %.2f, y: %.2f, z: %.2f",
                  stat.camera_rotation.x,
                  stat.camera_rotation.y,
                  stat.camera_rotation.z);
    }

    if (ImGui::CollapsingHeader("Objects", ImGuiTreeNodeFlags_DefaultOpen))
    {
    }

    ImGui::End();
  }

  void ImguiManager::windowControl(std::function<void()> fullScreen, std::function<void()> windowed)
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

  void ImguiManager::render()
  {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImguiManager::newFrame()
  {
    // Call this once per frame to initialize ImGui for the current frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }
} // namespace UI
