#include "imgui.h"
#include "gui.h"
#include "common.h"
#include <chrono>
#include <cstdlib>
#include <string>
#include <thread>
//----------------------------
// 主窗口关闭回调
//----------------------------
void Close() {
    logger->debug("exit");
}
void Hello() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
//----------------------------
// 主画面内容
//----------------------------
const char* items[] = {"111", "222", "333"};
void DrawContent() {
    static float f = 0.0f;
    static short index = 0;
    static bool state;
    ImGui::Title("WOW: Dear ImGui 桌面APP框架");
    // 基础组件
    ImGui::Section("基础组件");
    ImGui::BeginGroup();
    ImGui::Checkbox("形状", &state);
    ImGui::SameLine();
    ImGui::ToggleButton("圆形", &state, "方形");
    ImGui::SameLine();
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(200.0f);
    ImGui::CustomCombo("选择", items, 3, index, NULL);
    ImGui::PopItemWidth();
    ImGui::EndGroup();

    ImGui::Section("按钮&回调");
    static int counter = 0;
    ImGui::BeginGroup();
    if (ImGui::PrimaryButton("数据绑定")) {
        counter++;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::EndGroup();

    ImGui::Section("输入组件");
    // 输入组件
    static int num1 = 0;
    static float num2 = 0;
    static int num3[2] = {0, 0};
    static int num4[3] = {0, 0, 0};
    static int num5[4] = {0, 0, 0, 0};
    ImGui::BeginGroup();
    ImGui::PushItemWidth(250.0f);
    ImGui::InputInt("整数", &num1);
    ImGui::SameLine();
    ImGui::InputFloat("浮点数", &num2);
    ImGui::SameLine();
    ImGui::InputFloat("浮点数##1", &num2, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
    ImGui::PopItemWidth();
    ImGui::EndGroup();
    ImGui::BeginGroup();
    ImGui::PushItemWidth(250.0f);
    ImGui::InputInt2("2个整数", num3);
    ImGui::SameLine();
    ImGui::InputInt3("3个整数", num4);
    ImGui::SameLine();
    ImGui::InputInt4("4个整数", num5);
    ImGui::PopItemWidth();
    ImGui::EndGroup();
    // 任务类
    ImGui::Section("前后台任务");
    ImGui::BeginGroup();
    if(ImGui::Button("前台任务", ImVec2(ImGui::GetFontSize() * 6, 0))) {
        TaskManager::CreateGlobalTask("前台任务", Hello);
    }
    ImGui::SameLine();
    if(ImGui::Button("后台任务", ImVec2(ImGui::GetFontSize() * 6, 0))) {
        TaskManager::CreateBackendTask("后台任务", Hello);
    }
    ImGui::SameLine();
    if(ImGui::Button("消息窗口", ImVec2(ImGui::GetFontSize() * 6, 0))) {
        TaskManager::Message("消息窗口");
    }
    ImGui::SameLine();
    if(ImGui::Button("选择单个文件", ImVec2(ImGui::GetFontSize() * 8, 0))) {
    }
    ImGui::SameLine();
    if(ImGui::Button("选择多个文件", ImVec2(ImGui::GetFontSize() * 8, 0))) {
    }
    ImGui::SameLine();
    if(ImGui::Button("选择目录", ImVec2(ImGui::GetFontSize() * 8, 0))) {
        ImGui::GetFileName();
    }
    ImGui::SameLine();
    if(ImGui::Button("保存到文件", ImVec2(ImGui::GetFontSize() * 8, 0))) {
        ImGui::OpenPopup("文件选择");
    }
    ImGui::EndGroup();
    // 表格
    ImGui::Section("表格");
    if(ImGui::BeginTable("table", 5, ImGuiTableFlags_Borders)) {
        ImGui::TableSetupColumn("One");
        ImGui::TableSetupColumn("Two");
        ImGui::TableSetupColumn("Three");
        ImGui::TableSetupColumn("Four");
        ImGui::TableSetupColumn("Five");
        ImGui::TableHeadersRow();
        for(int i=0; i<3; i++) {
            for(int j=0; j<4; j++) {
                ImGui::TableNextColumn();
                ImGui::AlignTextToFramePadding();
                ImGui::Text("%d##%d", j, j);
            }
            ImGui::TableNextColumn();
            ImGui::Button(std::format("按钮{}##{}", i, i).c_str());
        }
        ImGui::EndTable();
    }
    // 子窗口
    ImGui::Section("子窗口");
    ImGui::BeginChild("Child", ImVec2(0, 0), ImGuiChildFlags_AlwaysUseWindowPadding);
    ImGui::BeginGroup();
    ImGui::Checkbox("形状##1", &state);
    ImGui::SameLine();
    ImGui::ToggleButton("圆形##1", &state, "方形");
    ImGui::SameLine();
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::PopItemWidth();
    ImGui::EndGroup();
    ImGui::EndChild();
}

bool another_dialog = false;

void DrawWindow() {
    auto style = ImGui::GetStyle();
    //----------------------------
    // 后台加载窗口
    //----------------------------
    if(State::backend_task_state == State::RUNNING) {
        ImGui::Begin("Loading", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
        ImGui::Spinner("Spinner", style.FontSizeBase, 6, Style::LoadingColor);
        ImGui::SetWindowPos(ImVec2(State::width - ImGui::GetWindowSize().x - style.WindowPadding.x, 0));
        ImGui::End();
    }
    static bool state;
    // ImGui::ShowDemoWindow(&state);
    if(another_dialog) {
        ImGui::Begin("Demo", &another_dialog, ImGuiWindowFlags_NoCollapse); 
        ImGui::Checkbox("形状##1", &state);
        ImGui::SameLine();
        ImGui::ToggleButton("圆形", &state, "方形");
        ImGui::End();
    }
}


void DrawPopup() {
    auto style = ImGui::GetStyle();
    //----------------------------
    // 全局加载窗口
    //----------------------------
    switch (State::global_task_state) {
        case State::READY:
            break;
        case State::START:
        case State::STOP:
        case State::RUNNING:
            if(ImGui::BeginPopupModal("GlobalLoading", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)) {
                ImGui::Spinner("Spinner", style.FontSizeBase, 6, Style::LoadingColor);
                ImGui::EndPopup();
            }
            if(State::global_task_state == State::START) {
                ImGui::OpenPopup("GlobalLoading");
                State::global_task_state = State::RUNNING;
            } else if (State::global_task_state == State::STOP) {
                ImGui::CloseCurrentPopup();
                State::global_task_state = State::READY;
            }
            break;
    }
    //----------------------------
    // 消息窗口
    //----------------------------
    switch (State::global_msg_state) {
        case State::READY:
        case State::STOP:
            break;
        case State::RUNNING:
        case State::START:
            if(ImGui::BeginPopupModal("注意", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("%s", State::msg.c_str());
                ImGui::BeginGroup();
                if(ImGui::Button("确定", ImVec2(style.FontSizeBase * State::scale * 6, 0))){
                    if(State::confirm != NULL) {
                        State::confirm();
                        State::confirm = NULL;
                    }
                    ImGui::CloseCurrentPopup();
                    State::global_msg_state = State::READY;
                };
                if(State::confirm != NULL) {
                    ImGui::SameLine();
                    if(ImGui::Button("取消", ImVec2(style.FontSizeBase * State::scale * 6, 0))){
                        ImGui::CloseCurrentPopup();
                        State::global_msg_state = State::READY;
                    };
                }
                ImGui::EndGroup();
                ImGui::EndPopup();
            }
            if(State::global_msg_state == State::START) {
                ImGui::OpenPopup("注意");
                State::global_msg_state = State::RUNNING;
            }
            break;
    }
    //----------------------------
    // 文件窗口
    //----------------------------
    switch (State::global_msg_state) {
        case State::READY:
        case State::STOP:
        case State::RUNNING:
        case State::START:
            break;
    }
}


void Draw() {
    //----------------------------
    // 主窗口渲染
    //----------------------------
    DrawWindow();
    DrawPopup();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
    ImGui::Begin("main", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings);
    ImGui::FileDialog();
    DrawContent();
    if (ImGui::GetWindowPos().y != 0) {
        ImGui::SetWindowSize(ImVec2(State::width, State::height));
        ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
    }
    ImGui::End();
    ImGui::PopStyleVar();
}
