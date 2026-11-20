#include "wow_widgets.h"
#include "imgui.h"
#include <cstdarg>


void WowWidgets::SizedText(float scale, const char* fmt, ...) {
    ImGui::SetWindowFontScale(scale);
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);
    ImGui::SetWindowFontScale(1.0f);
}

void WowWidgets::SizedTextColored(const ImVec4& col, float scale, const char* fmt, ...) {
    ImGui::SetWindowFontScale(scale);
    va_list args;
    va_start(args, fmt);
    ImGui::TextColoredV(col, fmt, args);
    va_end(args);
    ImGui::SetWindowFontScale(1.0f);
}

