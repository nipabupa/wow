#include "imgui.h"
#include "style.h"
#include "common.h"
#include <string>
#include <thread>


//----------------------------
// 全局状态初始化
//----------------------------
bool is_loading = false;
bool is_global_loading = false;
std::string msg;
void (*confirm)() = NULL; // 是否点击确认回调

//----------------------------
// 窗口关闭回调
//----------------------------
void Close() {
    logger->debug("exit");
}

//----------------------------
// 主画面内容
//----------------------------
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
    if (ImGui::PrimaryButton("数据刷新")) {
        counter++;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    if (ImGui::DangerButton("消息窗口")) {
        msg = "123123123";
        confirm = Close;
        ImGui::OpenPopup("Warn");
    }
    if (ImGui::Button("全局加载")) {
        ImGui::OpenPopup("GlobalLoading");
    }
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
    // 全局加载窗口
    if(ImGui::BeginPopupModal("GlobalLoading", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)) {
        ImGui::Spinner("Spinner", style.FontSizeBase, 6, LoadingColor);
        ImGui::EndPopup();
    }
    // 消息窗口
    if(ImGui::BeginPopupModal("Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
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
    if(is_global_loading) {
        ImGui::OpenPopup("GlobalLoading");
    } else {
        if(ImGui::IsPopupOpen("GlobalLoading")) {
            ImGui::EndPopup();
        }
    }
    Content();
    if (ImGui::GetWindowPos().y != 0) {
        ImGui::SetWindowSize(ImVec2(width, height));
        ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
    }
    ImGui::End();
    ImGui::PopStyleVar();
}
