#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_extends.h"


namespace ImGui {
    static ImGuiExtendStyle imgui_extend_style;

    ImGuiExtendStyle& GetExtendStyle() {
        return imgui_extend_style;
    }

    void Title(const char* label, const ImVec4* color) {
        PushFont(NULL, GetStyle().FontSizeBase + 8);
        if(color == nullptr) {
            TextColored(*color, "%s", label);
        } else {
            TextUnformatted(label);
        }
        PopFont();
    }

    void Section(const char* label, const ImVec4* color) {
        PushFont(NULL, GetStyle().FontSizeBase + 4);
        if(color == nullptr) {
            TextColored(*color, "%s", label);
        } else {
            TextUnformatted(label);
        }
        PopFont();
    }

    bool PrimaryButton(const char* label, const ImVec2& size) {
        PushStyleColor(ImGuiCol_Text, imgui_extend_style.PrimaryColor);
        auto state = Button(label);
        PopStyleColor();
        return state;
    }

    bool DangerButton(const char* label, const ImVec2& size) {
        PushStyleColor(ImGuiCol_Text, imgui_extend_style.DangerColor);
        auto state = Button(label, size);
        PopStyleColor();
        return state;
    }

    void BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) {
            return;
        }
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = size_arg;
        size.x -= style.FramePadding.x * 2;
        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id)) {
            return;
        }
        // Render
        const float circleStart = size.x * 0.7f;
        const float circleEnd = size.x;
        const float circleWidth = circleEnd - circleStart;
        window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
        window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart*value, bb.Max.y), fg_col);
        const float t = g.Time;
        const float r = size.y / 2;
        const float speed = 1.5f;
        const float a = speed*0;
        const float b = speed*0.333f;
        const float c = speed*0.666f;
        const float o1 = (circleWidth+r) * (t+a - speed * (int)((t+a) / speed)) / speed;
        const float o2 = (circleWidth+r) * (t+b - speed * (int)((t+b) / speed)) / speed;
        const float o3 = (circleWidth+r) * (t+c - speed * (int)((t+c) / speed)) / speed;
        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);
    }

    void Spinner(const char* label, float radius, int thickness, const ImVec4& color) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) {
            return;
        }
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size((radius )*2, (radius + style.FramePadding.y)*2);
        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id)) {
            return;
        }
        // Render
        window->DrawList->PathClear();
        int num_segments = 30;
        int start = abs(ImSin(g.Time*1.8f)*(num_segments-5));
        const float a_min = IM_PI*2.0f * ((float)start) / (float)num_segments;
        const float a_max = IM_PI*2.0f * ((float)num_segments-3) / (float)num_segments;
        const ImVec2 centre = ImVec2(pos.x+radius, pos.y+radius+style.FramePadding.y);
        for (int i = 0; i < num_segments; i++) {
            const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
            window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a+g.Time*8) * radius, centre.y + ImSin(a+g.Time*8) * radius));
        }
        window->DrawList->PathStroke(ColorConvertFloat4ToU32(color), false, thickness);
    }

    void ToggleButton(const char* str_id, bool* v, const char* other_label) {
        auto& style = GetStyle();
        const ImGuiExtendStyle& style_ = GetExtendStyle();
        BeginGroup();
        AlignTextToFramePadding();
        PushStyleVarX(ImGuiStyleVar_ItemSpacing, style.FontSizeBase / 2);
        TextUnformatted(other_label);
        SameLine();
        ImVec2 p = GetCursorScreenPos();
        ImDrawList* draw_list = GetWindowDrawList();
        float height = GetFrameHeight();
        float width = height * 1.55f;
        float radius = height * 0.50f;
        InvisibleButton(str_id, ImVec2(width, height));
        if (IsItemClicked()) *v = !*v;
        float t = *v ? 1.0f : 0.0f;
        ImGuiContext& g = *GImGui;
        float ANIM_SPEED = 0.08f;
        if (g.LastActiveId == g.CurrentWindow->GetID(str_id)) {
            float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
            t = *v ? (t_anim) : (1.0f - t_anim);
        }
        ImU32 col_bg;
        if (IsItemHovered())
            col_bg = GetColorU32(ImLerp(style.Colors[ImGuiCol_FrameBgHovered], ImGui::ColorConvertU32ToFloat4(style_.SecondaryColor), t));
        else
            col_bg = GetColorU32(ImLerp(style.Colors[ImGuiCol_FrameBg], ImGui::ColorConvertU32ToFloat4(style_.PrimaryColor), t));
        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
        draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
        SameLine();
        TextUnformatted(str_id);
        PopStyleVar();
        EndGroup();
    }

    void CustomCombo(const char* label, const char* items[], short size, short& index, void (*callback)(), int flags) {
        if (BeginCombo(label, items[index], flags)) {
            for (int n = 0; n < size; n++) {
                const bool is_selected = (index == n);
                if (Selectable(items[n], is_selected)) {
                    index = n;
                    if (callback != NULL) {
                        callback();
                    }
                }
                if (is_selected) {
                    SetItemDefaultFocus();
                }
            }
            EndCombo();
        }
    }
}
