#include "wow_widgets.h"


bool ImGui::CustomButton(const char* label, const ImVec2& size, ImGui::WowType type) {
    switch (type) {
        case ImGui::WowType::WOW_PRIMARY:
            break;
        case ImGui::WowType::WOW_WARN:
            break;
        case ImGui::WowType::WOW_DANGER:
            break;
        default:
            break;
    }
    bool state = ImGui::Button(label, size);
    ImGui::PopStyleColor();
    return state;
}

void ImGui::SizedText(float scale, const char* fmt, ...) {
    ImGui::SetWindowFontScale(scale);
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);
    ImGui::SetWindowFontScale(1.0f);
}

void ImGui::SizedTextColored(const ImVec4& col, float scale, const char* fmt, ...) {
    ImGui::SetWindowFontScale(scale);
    va_list args;
    va_start(args, fmt);
    ImGui::TextColoredV(col, fmt, args);
    va_end(args);
    ImGui::SetWindowFontScale(1.0f);
}
