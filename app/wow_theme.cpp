#include "wow_theme.h"
#include "imgui.h"


WowTheme::WowTheme() {
}

void WowTheme::Load() {

}

void ::WowTheme::buildStyle() {
    ImGui::StyleColorsDark();
    auto& style = ImGui::GetStyle();
    style.FontSizeBase = fontBase_;
    style.FontScaleDpi = scale_;
    // Main
    style.FrameRounding = 4;
    style.WindowPadding = ImVec2(15, 15);
    style.FramePadding = ImVec2(10, 5);
    style.ItemSpacing = ImVec2(10, 8);
    style.ItemInnerSpacing = ImVec2(10, 8);
    style.GrabMinSize = 15;
    // Border
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 2;
    style.PopupBorderSize = 2;
    style.FrameBorderSize = 0;
    // Rounding
    style.WindowRounding = 10;
    style.FrameRounding = 4;
    style.PopupRounding = 10;
    style.GrabRounding = 4;
    style.MenuItemRounding = 0;
    // scrollbar
    style.ScrollbarSize = 12;
    style.ScrollbarRounding = 9;
    style.ScrollbarPadding = 2;
    // tab
    style.TabBorderSize = 0;
    style.TabBarBorderSize = 2;
    style.TabRounding = 4;
    // table
    style.CellPadding = ImVec2(8, 4);
    // img
    style.ImageRounding = 4;

    style.ScaleAllSizes(scale_);

    // Colors
}

void WowTheme::buildFonts(WowConfig& config) {
    // TODO FreeType Font
    ImGuiIO& io = ImGui::GetIO();
    // 支持键盘控制
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    static const ImWchar icon_ranges[] = { 0xE000, 0xF8FF, 0 };  // Nerd Font
    // 中文字体
    ImFontConfig baseConfig;
    baseConfig.GlyphExcludeRanges = icon_ranges;
    ImFont* baseFont = io.Fonts->AddFontFromFileTTF(config.baseFontPath_.c_str(), fontBase_, &baseConfig);
    // Icon字体
    ImFontConfig iconConfig;
    iconConfig.MergeMode = true;
    ImFont* iconFont = io.Fonts->AddFontFromFileTTF(config.iconFontPath_.c_str(), fontBase_, &iconConfig, icon_ranges);
}
