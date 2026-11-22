#pragma once
#include "imgui.h"


namespace ImGui {
    enum WowType {
        WOW_PRIMARY,
        WOW_WARN,
        WOW_DANGER,
        WOW_INFO,
    };
    bool CustomButton(const char* label, const ImVec2& size, WowType type = WOW_INFO);
    // 可调尺寸文本
    void SizedText(float scale, const char* fmt, ...);
    // 可调尺寸彩色文本
    void SizedTextColored(const ImVec4& col, float scale, const char* fmt,...);
    // 可调尺寸table
    // loading
}
