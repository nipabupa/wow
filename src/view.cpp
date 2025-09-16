#include "imgui.h"
#include "app.h"

// Our state
bool show_demo_window = true;
bool show_another_window = false;
bool is_loading = false;


void FrameText(const char *text) {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().FramePadding.y);
    ImGui::TextUnformatted(text);
}


void Draw(int width, int height) {
    auto& style = ImGui::GetStyle();
    static float f = 0.0f;
    static int counter = 0;
    //----------------------------
    // 功能窗口渲染
    //----------------------------
    if(is_loading) {
        ImGui::Begin("Loading", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
        ImGui::Spinner("Spinner", style.FontSizeBase, 6, LoadingColor);
        ImGui::SetWindowPos(ImVec2(width - ImGui::GetWindowSize().x - style.WindowPadding.x, 0));
        ImGui::End();
    }
    //----------------------------
    // 主窗口渲染
    //----------------------------
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
    ImGui::Begin("main", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::Title("你好");
    ImGui::Checkbox("Demo Window", &show_demo_window);
    ImGui::Checkbox("Another Window", &show_another_window);
    ImGui::PushItemWidth(200.0f);
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::PopItemWidth();
    ImGui::ToggleButton("状态", &show_another_window);
    if (ImGui::Button("Button1")) {
        counter++;
    }
    if (ImGui::PrimaryButton("Button2")) {
        counter++;
    }
    if (ImGui::DangerButton("Button3")) {
        counter++;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    if (ImGui::GetWindowPos().x != 0) {
        ImGui::SetWindowSize(ImVec2(width, height));
        ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
    }
    ImGui::End();
    ImGui::PopStyleVar();
    //----------------------------
    // 独立窗口渲染
    //----------------------------
}
