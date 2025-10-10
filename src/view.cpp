#include <chrono>
#include "imgui.h"
#include "wow.h"
#include "common.h"
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
    ImGui::SameLine();
    static int counter = 0;
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
    ImGui::PushItemWidth(350.0f);
    ImGui::InputInt("整数", &num1);
    ImGui::SameLine();
    ImGui::InputFloat("浮点数", &num2);
    ImGui::SameLine();
    ImGui::InputFloat("浮点数##1", &num2, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
    ImGui::PopItemWidth();
    ImGui::EndGroup();
    ImGui::BeginGroup();
    ImGui::PushItemWidth(350.0f);
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
        App::CreateGlobalTask("前台任务", Hello);
    }
    ImGui::SameLine();
    if(ImGui::Button("后台任务", ImVec2(ImGui::GetFontSize() * 6, 0))) {
        App::CreateBackendTask("后台任务", Hello);
    }
    ImGui::SameLine();
    if(ImGui::Button("消息窗口", ImVec2(ImGui::GetFontSize() * 6, 0))) {
        App::message_dialog.Open("消息窗口");
    }
    ImGui::SameLine();
    if(ImGui::Button("选择文件", ImVec2(ImGui::GetFontSize() * 8, 0))) {
        App::file_dialog.ChangeToSelectFiles();
        App::file_dialog.SetFilter({"h", "cpp"});
        App::file_dialog.Open();
    }
    ImGui::SameLine();
    if(ImGui::Button("选择目录", ImVec2(ImGui::GetFontSize() * 8, 0))) {
        App::file_dialog.ChangeToSelectDirectory();
        App::file_dialog.Open();
    }
    ImGui::SameLine();
    if(ImGui::Button("保存到文件", ImVec2(ImGui::GetFontSize() * 8, 0))) {
        App::file_dialog.ChangeToSaveFile();
        App::file_dialog.Open();
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

void DrawWindow() {
    App::backend_loading.Display();
    App::global_loading.Display();
    App::message_dialog.Display();
    App::file_dialog.Display();
}

void Draw() {
    //----------------------------
    // 主窗口渲染
    //----------------------------
    DrawWindow();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
    ImGui::Begin("main", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings);
    DrawContent();
    if (ImGui::GetWindowPos().y != 0) {
        ImGui::SetWindowSize(ImVec2(App::width, App::height));
        ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
    }
    ImGui::End();
    ImGui::PopStyleVar();
}
