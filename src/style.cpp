# include "imgui.h"


void InitStyle(float scale) {
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.FontScaleDpi = scale;
    style.FontScaleMain = scale;
    style.FontSizeBase = 20.0f;
    // size
    style.WindowPadding = ImVec2(style.FontSizeBase, style.FontSizeBase);
    style.WindowBorderSize = 1.0f;
    style.WindowRounding = style.FontSizeBase / 2;
    style.ScrollbarSize = style.FontSizeBase / 2;
    style.ItemSpacing = ImVec2(style.FontSizeBase, style.FontSizeBase);
    style.ItemInnerSpacing = ImVec2(style.FontSizeBase / 2, 0);
    style.FramePadding = ImVec2(style.FontSizeBase / 2, style.FontSizeBase / 2);
    style.FrameRounding = style.FontSizeBase / 4;
    style.ChildBorderSize = 2.0f;
    style.ChildRounding = style.FontSizeBase / 4;
    style.PopupRounding = style.FontSizeBase / 4;
    style.CellPadding = ImVec2(style.FontSizeBase / 2, style.FontSizeBase / 4);
    // color
    auto colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.125f, 0.125f, 0.125f, 1.0f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.153f, 0.153f, 0.153f, 1.0f);
    colors[ImGuiCol_Border] = ImVec4(0.153f, 0.153f, 0.153f, 1.0f);
    colors[ImGuiCol_Text] = ImVec4(0.808f, 0.808f, 0.808f, 1.0f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.463f, 0.463f, 0.463f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.192f, 0.192f, 0.208f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.231f, 0.231f, 0.243f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.271f, 0.271f, 0.282f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.192f, 0.192f, 0.208f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.231f, 0.231f, 0.243f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.271f, 0.271f, 0.282f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
    style.ScaleAllSizes(scale);
}


namespace ImGui {
    void Title(const char* label) {
        ImGui::PushFont(NULL, ImGui::GetStyle().FontSizeBase + 5);
        ImGui::PushStyleColor(ImGuiCol_Text, 0x54A9FFFF);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
        ImGui::Text("%s", label);
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        ImGui::PopFont();
    }

    bool PrimaryButton(const char* label, const ImVec2& size) {
        ImGui::PushStyleColor(ImGuiCol_Text, 0x54A9FFFF);
        auto state = ImGui::Button(label, size);
        ImGui::PopStyleColor();
        return state;
    }

    bool DangerButton(const char* label, const ImVec2& size) {
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFC724EFF);
        auto state = ImGui::Button(label, size);
        ImGui::PopStyleColor();
        return state;
    }
}
