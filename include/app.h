#include "imgui.h"
#define IMPLOT_ENABLED

// 常量
const ImVec4 BackgroundColor = ImVec4(0.125f, 0.125f, 0.125f, 1.0f);
const ImVec4 CardColor = ImVec4(0.153f, 0.153f, 0.153f, 1.0f);
const ImVec4 PrimaryColor = ImVec4(0.329f, 0.663f, 1.0f, 1.0f);
const ImVec4 SecondColor = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
const ImVec4 DangerColor = ImVec4(0.988f, 0.447f, 0.306f, 1.0f);
const ImVec4 LoadingColor = ImVec4(0.353f, 0.353f, 0.353f, 1.0f);

// 全局状态
extern bool is_loading;

// 全局方法
void InitStyle(float scale);
void Draw(int width, int height);

// 新增UI方法
namespace ImGui {
    void Title(const char* label);
    bool PrimaryButton(const char* label, const ImVec2& size = ImVec2(0, 0));
    bool DangerButton(const char* label, const ImVec2& size = ImVec2(0, 0));
    void Spinner(const char* label, float radius, int thickness, const ImVec4& color);
    void BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
    void ToggleButton(const char* str_id, bool* v);
}
