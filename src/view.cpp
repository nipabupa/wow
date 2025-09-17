#include "imgui.h"
#include "app.h"
#include <cstddef>
#include <iostream>


void Content() {
    static float f = 0.0f;
    static int counter = 0;
    static short index = 0;
    static bool state;
    ImGui::Title("你好");
    ImGui::PushItemWidth(200.0f);
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::PopItemWidth();
    ImGui::ToggleButton("原型", &state, "方形");
    ImGui::Checkbox("形状", &state);
    const char* items[] = {"111", "222", "333"};
    ImGui::CustomCombo("选择", items, 3, index);
    if (ImGui::PrimaryButton("Button1")) {
        counter++;
    }
    if (ImGui::DangerButton("Button2")) {
        msg = "123123123";
        confirm = Close;
        ImGui::OpenPopup("Warn");
    }
    ImGui::Text("counter = %d", counter);
}


void Close() {
    std::cout << "exit" << std::endl;
}


void Draw(int width, int height) {
    auto& style = ImGui::GetStyle();
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
    ImGui::Begin("main", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings);
    // 消息窗口
    if(ImGui::BeginPopupModal("Warn", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("%s", msg.c_str());
        ImGui::BeginGroup();
        if(ImGui::Button("确定", DefaultWidth)){
            if(confirm != NULL) {
                confirm();
                confirm = NULL;
            }
            ImGui::CloseCurrentPopup();
        };
        ImGui::SameLine();
        if(ImGui::Button("取消", DefaultWidth)){
            ImGui::CloseCurrentPopup();
        };
        ImGui::EndGroup();
        ImGui::EndPopup();
    }
    Content();
    if (ImGui::GetWindowPos().y != 0) {
        ImGui::SetWindowSize(ImVec2(width, height));
        ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
    }
    ImGui::End();
    ImGui::PopStyleVar();
}
