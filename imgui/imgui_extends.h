#pragma once
#include "imgui.h"
#include <vector>
#include <string>
#include <functional>
//----------------------------
// 新增ImGui组件
//----------------------------
namespace ImGui {
    //-------------------------
    // 新增控件
    //----------------------------
    void Spinner(const char* label, float radius, int thickness, const ImVec4& color);
    void BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
    void ToggleButton(const char* str_id, bool* v, const char* other_label);
    void CustomCombo(const char* label, const std::vector<std::string>& items, short& index, std::function<void(const short& index, const std::string& value)> callback = nullptr, int flags = ImGuiComboFlags_None);
}
