#include "imgui.h"
#include "imgui_internal.h"
#include "gui.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fileapi.h>
#include <filesystem>
#include <format>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#ifdef WIN32
#include <windows.h>
#endif


void InitStyle() {
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.FontScaleDpi = State::scale;
    style.FontSizeBase = Style::FontBase;
    // size
    style.WindowPadding = ImVec2(style.FontSizeBase, style.FontSizeBase);
    style.WindowBorderSize = 1.0f;
    style.WindowRounding = style.FontSizeBase / 2;
    style.ScrollbarSize = style.FontSizeBase / 2;
    style.ScrollbarRounding = style.FontSizeBase / 4;
    style.ChildRounding = style.FontSizeBase / 2;
    style.PopupRounding = style.FontSizeBase / 2;
    style.GrabRounding = style.FontSizeBase / 4;
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
    colors[ImGuiCol_WindowBg] = Style::BackgroundColor;
    colors[ImGuiCol_ChildBg] = Style::CardColor;
    colors[ImGuiCol_Border] = ImVec4(0.153f, 0.153f, 0.153f, 1.0f);
    colors[ImGuiCol_Text] = Style::TextColor;
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.463f, 0.463f, 0.463f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.192f, 0.192f, 0.208f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.231f, 0.231f, 0.243f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.271f, 0.271f, 0.282f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.192f, 0.192f, 0.208f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.231f, 0.231f, 0.243f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.271f, 0.271f, 0.282f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.105f, 0.105f, 0.105f, 0.8f);
    colors[ImGuiCol_PopupBg] = Style::CardColor;
    style.ScaleAllSizes(State::scale);
}


namespace ImGui {
    void Title(const char* label, const ImVec4& color) {
        PushFont(NULL, GetStyle().FontSizeBase + 8);
        TextColored(color, "%s", label);
        PopFont();
    }

    void Section(const char* label, const ImVec4& color) {
        PushFont(NULL, GetStyle().FontSizeBase + 4);
        TextColored(color, "%s", label);
        PopFont();
    }

    bool PrimaryButton(const char* label, const ImVec2& size) {
        PushStyleColor(ImGuiCol_Text, Style::PrimaryColor);
        auto state = Button(label, size);
        PopStyleColor();
        return state;
    }

    bool DangerButton(const char* label, const ImVec2& size) {
        PushStyleColor(ImGuiCol_Text, Style::DangerColor);
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
        auto style = GetStyle();
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
            col_bg = GetColorU32(ImLerp(style.Colors[ImGuiCol_FrameBgHovered], Style::SecondColor, t));
        else
            col_bg = GetColorU32(ImLerp(style.Colors[ImGuiCol_FrameBg], Style::PrimaryColor, t));
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


bool _compare(FileInfo a, FileInfo b) {
    if(a.is_directory && !b.is_directory) {
        return true;
    }
    if(!a.is_directory && b.is_directory) {
        return false;
    }
    return std::strcmp(a.filename, b.filename) == -1;
}

FileDialog::FileDialog() {
    is_save_file = false;
    is_directory = false;
    // auto home = std::getenv("Home");
    // const_directory.push_back({"Home", home});
#ifdef WIN32
    // const_directory.push_back({"桌面", std::format("{}\\Desktop", home)});
    // char buffer[256];
    // DWORD length = GetLogicalDriveStringsA(255, buffer);
    // for(int i=0; i<length; i++) {
    //     auto tmp = std::format("{}:\\", buffer[i]);
    //     const_directory.push_back({tmp, tmp});
    // }
#else
    const_directory.push_back({"桌面", std::format("{}/Desktop", home)});
#endif
}

void FileDialog::ChangeToSaveFile() {
    is_save_file = true;
}

void FileDialog::ChangeToSelectDirectory() {
    is_directory = true;
}

void FileDialog::SetFilter(std::vector<std::string> filters) {
    exts = filters;
}

void FileDialog::UpdateFileInfo(const char* dirname) {
    std::strcpy(file_directory, dirname);
    fileinfo_list.clear();
    for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
        if(is_directory && !entry.is_directory()) {
            continue;
        }
        bool flag = false;
        for (auto filter : exts) {
            if(entry.path().filename().string().ends_with(filter)) {
                flag = true;
            }
        }
        if(!flag) {
            continue;
        }
        FileInfo tmp;
        std::strcpy(tmp.filename, entry.path().filename().string().c_str());
        tmp.is_checked = false;
        tmp.is_directory = entry.is_directory();
        fileinfo_list.push_back(tmp);
    }
    std::sort(fileinfo_list.begin(), fileinfo_list.end(), _compare);
}

void FileDialog::Display() {
    // if(fileinfo_list.size() <= 0) {
    //     UpdateFileInfo(std::getenv("Home"));
    // }
    if(ImGui::BeginPopupModal("FileDialog", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings)) {
        // 当前目录
        ImGui::BeginGroup();
        if(ImGui::PrimaryButton("确定##FileDialog")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if(ImGui::Button("上一级")) {
            std::filesystem::path tmp = file_directory;
            UpdateFileInfo(tmp.parent_path().string().c_str());
        }
        ImGui::SameLine();
        ImGui::TextColored(Style::PrimaryColor, "当前目录: %s", file_directory);
        ImGui::EndGroup();
        // 输入
        if(is_save_file) {
            ImGui::PushItemWidth(200);
            ImGui::InputText("输入文件名", file_name, 256);
            ImGui::PopItemWidth();
        }
        // 内容
        ImGui::BeginGroup();
        {
            ImGui::BeginGroup();
            for(auto p : const_directory) {
                if(ImGui::Button(std::format("{}##FileDialog", p.first).c_str(), ImVec2(100, 0))) {
                    UpdateFileInfo(p.second.c_str());
                };
            }
            ImGui::EndGroup();
        }
        ImGui::SameLine();
        {
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));
            if(ImGui::BeginTable("文件信息", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY, ImVec2(600, 300))) {
                ImGui::TableSetupColumn("选择", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("文件", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("操作", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableHeadersRow();
                for (auto& fileinfo : fileinfo_list) {
                    ImGui::TableNextColumn();
                    ImGui::Checkbox(std::format("##{}", fileinfo.filename).c_str(), &fileinfo.is_checked);
                    ImGui::TableNextColumn();
                    if(fileinfo.is_directory) {
                        ImGui::TextColored(Style::PrimaryColor, "[D] %s", fileinfo.filename);
                        ImGui::TableNextColumn();
                        if(ImGui::Button(std::format("进入##{}", fileinfo.filename).c_str())) {
                            std::filesystem::path tmp = file_directory;
                            tmp.append(fileinfo.filename);
                            UpdateFileInfo(tmp.string().c_str());
                        }
                    } else {
                        ImGui::Text("[F] %s", fileinfo.filename);
                        ImGui::TableNextColumn();
                    }
                }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar();
        }
        ImGui::EndGroup();
        ImGui::EndPopup();
    }
}

void FileDialog::Open() {
    std::cout << 12 << std::endl;
    ImGui::OpenPopup("FileDialog");
}

std::string FileDialog::GetFileName() {
    if(fileinfo_list.empty()) {
        return "";
    } else {
        for (auto fileinfo : fileinfo_list) {
            if(fileinfo.is_checked) {
                std::cout << file_directory << '/' << fileinfo.filename << std::endl;
                return fileinfo_list.begin()->filename;
            }
        }
        return "";
    }
}
