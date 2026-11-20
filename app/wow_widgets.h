#pragma once
#include "imgui.h"


namespace WowWidgets {
    bool PrimaryButton(const char* label, const ImVec2& size);
    bool DangerButton(const char* label, const ImVec2& size);
    // 可调尺寸文本
    void SizedText(float scale, const char* fmt, ...);
    // 可调尺寸彩色文本
    void SizedTextColored(const ImVec4& col, float scale, const char* fmt,...);
    // 可调尺寸table
    // loading
}
