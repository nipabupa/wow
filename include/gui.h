#include <functional>
#include <string>
#include "imgui.h"
#include "imfilebrowser.h"
//----------------------------
// 风格常量
//----------------------------
namespace Style {
    const float FontBase = 16.0f;
    const ImVec4 BackgroundColor = ImVec4(0.125f, 0.125f, 0.125f, 1.0f);
    const ImVec4 CardColor = ImVec4(0.140f, 0.140f, 0.140f, 1.0f);
    const ImVec4 PrimaryColor = ImVec4(0.329f, 0.663f, 1.0f, 1.0f);
    const ImVec4 SecondColor = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
    const ImVec4 DangerColor = ImVec4(0.988f, 0.447f, 0.306f, 1.0f);
    const ImVec4 LoadingColor = ImVec4(0.353f, 0.353f, 0.353f, 1.0f);
    const ImVec4 TextColor = ImVec4(0.808f, 0.808f, 0.808f, 1.0f);
    const ImVec2 AutoSize = ImVec2(0, 0);
    const ImU32 RedColor = IM_COL32(255, 0, 0, 255);
    const ImU32 GreenColor = IM_COL32(0, 255, 0, 255);
}
//----------------------------
// 生命周期Hook
//----------------------------
void InitStyle();
void Draw();
void Close();
//----------------------------
// 全局状态
//----------------------------
namespace State {
    enum TaskState {
        READY,
        START,
        RUNNING,
        STOP,
    };
    // 缩放比例
    extern float scale;
    // 实时窗口尺寸
    extern int width;
    extern int height;
    // 后台任务运行状态
    extern TaskState backend_task_state;
    // 全局任务运行状态
    extern TaskState global_task_state;
    // 全局消息状态
    extern TaskState global_msg_state;
    // 消息窗口内容
    extern std::string msg;
    // 消息窗口确认回调
    extern std::function<void()> confirm; // 是否点击确认回调
    // 是否有任务运行
    bool IsRunning();
}
//----------------------------
// 新增ImGui组件
//----------------------------
namespace ImGui {
    void Title(const char* label, const ImVec4& color = Style::TextColor);
    void Section(const char* label, const ImVec4& color = Style::TextColor);
    bool PrimaryButton(const char* label, const ImVec2& size = Style::AutoSize);
    bool DangerButton(const char* label, const ImVec2& size = Style::AutoSize);
    void Spinner(const char* label, float radius, int thickness, const ImVec4& color);
    void BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
    void ToggleButton(const char* str_id, bool* v, const char* other_label);
    void CustomCombo(const char* label, const char* items[], short size, short& index, void (*callback)() = NULL, int flags = ImGuiComboFlags_None);
}
//----------------------------
// 任务管理
//----------------------------
namespace TaskManager {
    // 创建消息
    void Message(std::string message, std::function<void()> task = NULL);
    // 创建后台任务
    void CreateBackendTask(const char* title, std::function<void()> task);
    // 创建全局任务
    void CreateGlobalTask(const char* title, std::function<void()> task);
}

