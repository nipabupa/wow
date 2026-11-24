#include "app.h"
#include "imgui.h"
#include "wow_widgets.h"

const ImVec4 SECTON_TEXT_COLOR(255, 0, 0, 255);

Application::Application() {

}

Application::~Application() {

}

void Application::onSetup() {

}

bool Application::onClose() {
    return true;
}

void Application::build() {
    ImGui::TextColored(ImVec4(255, 0, 0, 255), "%s", "按钮");
    ImGui::TextColored(ImVec4(255, 0, 0, 255), "%s", "");
    // ImGui::Spinner("123", 30, 10, ImVec4(255, 255, 255, 255));
    // ImGui::BufferingBar("asdasda", 20, ImVec2(20, 20), 20, 20);
    const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
    const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);
    ImGui::Spinner("##spinner", 15, 6, col);
    static float a = 0.0f;
    ImGui::SliderFloat("123", &a, 0.0f, 1.0f);
    ImGui::BufferingBar("##buffer_bar", a, ImVec2(400, 6), bg, col);
    ImGui::ShowDemoWindow();
}


