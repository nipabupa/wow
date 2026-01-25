#pragma once
#include "imgui.h"
#include <vector>
#include <string>
#include <functional>
struct ImGuiColor {
    ImU32 u32;
    ImVec4 vec4;
};
//-------------------------
// 扩展Style
//----------------------------
struct ImGuiExtendStyle {
    ImGuiColor PrimaryColor;
    ImGuiColor SecondaryColor;
    ImGuiColor SuccessColor;
    ImGuiColor WarnColor;
    ImGuiColor DangerColor;
    ImGuiColor LoadingColor;
    ImGuiColor RedColor;
    ImGuiColor GreenColor;
    ImGuiColor BlueColor;

    ImGuiExtendStyle();
};
//----------------------------
// 新增ImGui组件
//----------------------------
namespace ImGui {
    ImGuiExtendStyle& GetExtendStyle();
    //-------------------------
    // 新增控件
    //----------------------------
    void Title(const char* label, const ImVec4* color = nullptr, int larger = 4);
    void Section(const char* label, const ImVec4* color = nullptr, int larger = 4);
    bool PrimaryButton(const char* label, const ImVec2& size = ImVec2(0, 0));
    bool DangerButton(const char* label, const ImVec2& size = ImVec2(0, 0));
    void Spinner(const char* label, float radius, int thickness, const ImVec4& color);
    void BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
    void ToggleButton(const char* str_id, bool* v, const char* other_label);
    void CustomCombo(const char* label, const std::vector<std::string> items, short& index, std::function<void(const short& index, const std::string& value)> callback = nullptr, int flags = ImGuiComboFlags_None);
}
