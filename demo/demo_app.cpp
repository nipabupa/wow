#include "demo_app.h"
#include "imgui.h"
#include "imgui_extends.h"
#include "implot.h"


DemoApp::DemoApp() {
    config.name_ = "Demo";
}

void DemoApp::build() {
    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();

    const static std::vector<std::string> items = {"111", "222", "333"};
    auto font_size = ImGui::GetFontSize();
    static float f = 0.0f;
    static short index = 0;
    static bool state;
    ImGui::Title("WOW: Dear ImGui 桌面APP框架");
    // // 基础组件
    // ImGui::Section("基础组件");
    // ImGui::BeginGroup();
    // ImGui::Checkbox("形状", &state);
    // ImGui::SameLine();
    // ImGui::ToggleButton("圆形", &state, "方形");
    // ImGui::SameLine();
    // ImGui::PushItemWidth(150.0f);
    // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    // ImGui::PopItemWidth();
    // ImGui::SameLine();
    // ImGui::PushItemWidth(200.0f);
    // ImGui::CustomCombo("选择", items, index, NULL);
    // ImGui::PopItemWidth();
    // ImGui::SameLine();
    // static int counter = 0;
    // if (ImGui::PrimaryButton("数据绑定")) {
    //     counter++;
    // }
    // ImGui::SameLine();
    // ImGui::Text("counter = %d", counter);
    // ImGui::EndGroup();
    //
    // ImGui::Section("输入组件");
    // // 输入组件
    // static int num1 = 0;
    // static float num2 = 0;
    // static int num3[2] = {0, 0};
    // static int num4[3] = {0, 0, 0};
    // static int num5[4] = {0, 0, 0, 0};
    // ImGui::BeginGroup();
    // ImGui::PushItemWidth(350.0f);
    // ImGui::InputInt("整数", &num1);
    // ImGui::SameLine();
    // ImGui::InputFloat("浮点数", &num2);
    // ImGui::SameLine();
    // ImGui::InputFloat("浮点数##1", &num2, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
    // ImGui::PopItemWidth();
    // ImGui::EndGroup();
    // ImGui::BeginGroup();
    // ImGui::PushItemWidth(350.0f);
    // ImGui::InputInt2("2个整数", num3);
    // ImGui::SameLine();
    // ImGui::InputInt3("3个整数", num4);
    // ImGui::SameLine();
    // ImGui::InputInt4("4个整数", num5);
    // ImGui::PopItemWidth();
    // ImGui::EndGroup();
    // // 任务类
    // ImGui::Section("前后台任务");
    // ImGui::BeginGroup();
    // if(ImGui::Button("前台任务", ImVec2(font_size * 6, 0))) {
    //     WowTask::CreateGlobalTask(MyTaskWithoutMessage);
    // }
    // ImGui::SameLine();
    // if(ImGui::Button("后台任务", ImVec2(font_size * 6, 0))) {
    //     WowTask::CreateBackendTask(MyTaskWithMessage);
    // }
    // ImGui::SameLine();
    // if(ImGui::Button("消息窗口", ImVec2(font_size * 6, 0))) {
    //     WowDialog::message_dialog.Open("消息窗口");
    // }
    // ImGui::SameLine();
    // if(ImGui::Button("选择文件", ImVec2(font_size * 8, 0))) {
    //     WowDialog::file_dialog.ChangeToSelectFiles({"h", "cpp"});
    //     WowDialog::file_dialog.Open();
    // }
    // ImGui::SameLine();
    // if(ImGui::Button("选择目录", ImVec2(font_size * 8, 0))) {
    //     WowDialog::file_dialog.ChangeToSelectDirectory();
    //     WowDialog::file_dialog.Open();
    // }
    // ImGui::SameLine();
    // if(ImGui::Button("保存到文件", ImVec2(font_size * 8, 0))) {
    //     WowDialog::file_dialog.ChangeToSaveFile({"h", "cpp"});
    //     WowDialog::file_dialog.Open();
    // }
    // ImGui::EndGroup();
    // 表格
    // ImGui::Section("表格");
    // if(ImGui::BeginTable("table", 5, ImGuiTableFlags_Borders)) {
    //     ImGui::TableSetupColumn("One");
    //     ImGui::TableSetupColumn("Two");
    //     ImGui::TableSetupColumn("Three");
    //     ImGui::TableSetupColumn("Four");
    //     ImGui::TableSetupColumn("Five");
    //     ImGui::TableHeadersRow();
    //     for(int i=0; i<3; i++) {
    //         for(int j=0; j<4; j++) {
    //             ImGui::TableNextColumn();
    //             ImGui::AlignTextToFramePadding();
    //             ImGui::Text("%d##%d", j, j);
    //         }
    //         ImGui::TableNextColumn();
    //         ImGui::Button(std::format("按钮{}##{}", i, i).c_str());
    //     }
    //     ImGui::EndTable();
    // }
    // // 子窗口
    // ImGui::Section("子窗口");
    // ImGui::BeginChild("Child", ImVec2(0, 0), ImGuiChildFlags_AlwaysUseWindowPadding);
    // ImGui::BeginGroup();
    // ImGui::Checkbox("形状##1", &state);
    // ImGui::SameLine();
    // ImGui::ToggleButton("圆形##1", &state, "方形");
    // ImGui::SameLine();
    // ImGui::PushItemWidth(150.0f);
    // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    // ImGui::PopItemWidth();
    // ImGui::EndGroup();
    // ImGui::EndChild();
}
