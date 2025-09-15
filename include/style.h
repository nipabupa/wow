#include "imgui.h"

void InitStyle(float scale);

namespace ImGui {
    void Title(const char* label);
    bool PrimaryButton(const char* label, const ImVec2& size = ImVec2(0, 0));
    bool DangerButton(const char* label, const ImVec2& size = ImVec2(0, 0));
}
