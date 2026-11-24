#pragma once
#include "imgui.h"
#include <vector>
#include <string>
#include <functional>


namespace ImGui {
    enum WowType {
        WOW_PRIMARY,
        WOW_WARN,
        WOW_DANGER,
        WOW_INFO,
    };
    // 可调尺寸文本
    void SizedText(float scale, const char* fmt, ...);
    // 可调尺寸彩色文本
    void SizedTextColored(const ImVec4& col, float scale, const char* fmt,...);
    // 自定义按钮
    bool CustomButton(const char* label, const ImVec2& size, WowType type = WOW_INFO);
    // 自定义Combo
    void CustomCombo(const char* label, const std::vector<std::string>& items, short& index, std::function<void(const short& index, const std::string& value)> callback = nullptr, int flags = ImGuiComboFlags_None);
    // 可调尺寸table
    void Spinner(const char* label, float radius, int thickness, const ImVec4& color);
    bool Spinner(const char* label, float radius, int thickness, const ImU32& color);
    void BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
}
