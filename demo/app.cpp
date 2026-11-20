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
    WowWidgets::SizedTextColored(ImVec4(255, 0, 0, 255), 1.2, "%s", "按钮");
    ImGui::ShowDemoWindow();
}
