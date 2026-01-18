#include "imgui.h"
//-------------------------
// 扩展Style
//----------------------------
struct ImGuiExtendStyle {
    ImU32 PrimaryColor = IM_COL32(84, 169, 255, 255);
    ImU32 SecondaryColor = IM_COL32(84, 169, 255, 150);
    ImU32 SuccessColor = IM_COL32(93, 194, 100, 255);
    ImU32 WarnColor = IM_COL32(255, 174, 67, 255);
    ImU32 DangerColor = IM_COL32(252, 114, 78, 255);
    ImU32 LoadingColor = IM_COL32(90, 90, 90, 255);
    // 自定义颜色
    const ImU32 RedColor = IM_COL32(255, 0, 0, 255);
    const ImU32 GreenColor = IM_COL32(0, 255, 0, 255);
    const ImU32 BlueColor = IM_COL32(0, 0, 255, 255);
    // 自定义尺寸
    const ImVec2 AutoSize = ImVec2(0, 0);
};

//----------------------------
// 新增ImGui组件
//----------------------------
namespace ImGui {
    ImGuiExtendStyle& GetExtendStyle();
    //-------------------------
    // 新增控件
    //----------------------------
    void Title(const char* label, const ImVec4* color = nullptr);
    void Section(const char* label, const ImVec4* color = nullptr);
    bool PrimaryButton(const char* label, const ImVec2& size = ImVec2(0, 0));
    bool DangerButton(const char* label, const ImVec2& size = ImVec2(0, 0));
    void Spinner(const char* label, float radius, int thickness, const ImVec4& color);
    void BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
    void ToggleButton(const char* str_id, bool* v, const char* other_label);
    void CustomCombo(const char* label, const char* items[], short size, short& index, void (*callback)() = NULL, int flags = ImGuiComboFlags_None);
}
