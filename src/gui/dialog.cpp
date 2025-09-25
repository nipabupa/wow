#include <filesystem>
#include <iostream>
#include "stl.h"
#include "gui.h"
#include "imgui.h"
#ifdef WIN32
#include <windows.h>
#include <shlobj.h>
#endif


namespace App {
    void BackendLoading::Display() {
        auto font_size = ImGui::GetFontSize();
        auto style = ImGui::GetStyle();
        if(state == RUNNING) {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(font_size / 2, 0));
            ImGui::Begin("Loading", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
            ImGui::Spinner("Spinner", font_size, font_size / 2, Style::LoadingColor);
            ImGui::SetWindowPos(ImVec2(App::width - ImGui::GetWindowSize().x - style.WindowPadding.x, style.WindowPadding.y));
            ImGui::End();
            ImGui::PopStyleVar();
        }
    }

    void GlobalLoading::Display() {
        auto font_size = ImGui::GetFontSize();
        auto style = ImGui::GetStyle();
        if(state == READY) {
            return;
        }
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(font_size / 2, 0));
        if(ImGui::BeginPopupModal("GlobalLoading", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Spinner("Spinner", font_size, font_size / 2, Style::LoadingColor);
            ImGui::SetWindowPos(ImVec2((App::width - ImGui::GetWindowSize().x) / 2, font_size * 20));
            ImGui::EndPopup();
        }
        ImGui::PopStyleVar();
        if(state == START) {
            ImGui::OpenPopup("GlobalLoading");
            state = RUNNING;
        } else if (state == STOP) {
            ImGui::CloseCurrentPopup();
            state = READY;
        }
    }

    void MessageDialog::Display() {
        auto style = ImGui::GetStyle();
        auto font_size = ImGui::GetFontSize();
        if(state == READY || state == STOP) {
            return;
        }
        if(ImGui::BeginPopupModal("注意##MessageDialog", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::SetWindowPos(ImVec2((App::width - ImGui::GetWindowSize().x) / 2, font_size * 10));
            ImGui::Text("%s", message.c_str());
            ImGui::BeginGroup();
            if(ImGui::Button("确定", ImVec2(style.FontSizeBase * scale * 6, 0))){
                if(confirm != NULL) {
                    confirm();
                    confirm = NULL;
                }
                ImGui::CloseCurrentPopup();
                state = READY;
            };
            if(confirm != NULL) {
                ImGui::SameLine();
                if(ImGui::Button("取消", ImVec2(style.FontSizeBase * scale * 6, 0))){
                    ImGui::CloseCurrentPopup();
                    state = READY;
                };
            }
            ImGui::EndGroup();
            ImGui::EndPopup();
        }
        if(state == START) {
            ImGui::OpenPopup("注意##MessageDialog");
            state = RUNNING;
        }
    }

    bool _compare(FileInfo a, FileInfo b) {
        if(a.is_directory && !b.is_directory) {
            return true;
        }
        if(!a.is_directory && b.is_directory) {
            return false;
        }
        return a.filename <= b.filename;
    }

    FileDialog::FileDialog() {
        is_save_file = false;
        is_select_directory = false;
#ifdef WIN32
        char buffer[256];
        DWORD a = 255;
        if(GetUserNameA(buffer, &a)) {
            const_directory.push_back({"桌面", std::format("C:\\Users\\{}\\Desktop", buffer)});
        }
        DWORD length = GetLogicalDriveStringsA(255, buffer);
        for(int i=0; i<length; i++) {
            if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
                auto tmp = format("{}:\\", buffer[i]);
                const_directory.push_back({tmp, tmp});
            }
        }
#else
        auto home = std::getenv("Home");
        const_directory.push_back({"Home", home});
        const_directory.push_back({"桌面", std::format("{}/Desktop", home)});
#endif
    }

    void FileDialog::UpdateFileInfo(const str& dirname) {
        file_directory = dirname;
        fileinfo_list.clear();
        for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
            if(is_select_directory && !entry.is_directory()) {
                continue;
            }
            // bool flag = false;
            // for (auto filter : exts) {
            //     if(entry.path().filename().string().ends_with(filter)) {
            //         flag = true;
            //     }
            // }
            // if(!flag) {
            //     continue;
            // }
            FileInfo tmp;
            tmp.filename = entry.path().filename().string();
            tmp.is_checked = false;
            tmp.is_directory = entry.is_directory();
            fileinfo_list.push_back(tmp);
        }
        std::sort(fileinfo_list.begin(), fileinfo_list.end(), _compare);
    }

    void FileDialog::Display() {
        if(state == READY || state == STOP) {
            return;
        }
        if(fileinfo_list.size() <= 0 && const_directory.size() > 0) {
            UpdateFileInfo(const_directory.begin()->second);
        }
        auto font_size = ImGui::GetFontSize();
        ImVec2 button_size = ImVec2(font_size * 6, 0);
        std::filesystem::path current_path(file_directory);
        if(ImGui::BeginPopupModal("文件选择##FileDialog", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize)) {
            ImGui::SetWindowSize(ImVec2(font_size*70, font_size*35));
            // 当前目录
            ImGui::BeginGroup();
            if(ImGui::PrimaryButton("确定##FileDialog", button_size)) {
                for (auto& name : fileinfo_list) {
                    if(name.is_checked) {
                        std::cout << name.filename << std::endl;
                    }
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if(ImGui::Button("取消##FileDialog", button_size)) {
                fileinfo_list.clear();
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if(ImGui::Button("上一级##FileDialog", button_size)) {
                str target = current_path.parent_path().string();
                UpdateFileInfo(target);
            }
            ImGui::SameLine();
            ImGui::TextColored(Style::PrimaryColor, "当前目录: %s", file_directory.c_str());
            ImGui::EndGroup();
            // 输入
            if(is_save_file) {
                ImGui::PushItemWidth(font_size*40);
                ImGui::InputText("输入文件名##FileDialog", file_name, 256);
                ImGui::PopItemWidth();
            }
            // 内容
            ImGui::BeginGroup();
            ImGui::BeginGroup();
            ImGui::PushStyleVarY(ImGuiStyleVar_ItemSpacing, font_size / 4);
            for(auto p : const_directory) {
                if(ImGui::Button(std::format("{}##FileDialog", p.first).c_str(), ImVec2(100, 0))) {
                    UpdateFileInfo(p.second);
                };
            }
            ImGui::PopStyleVar();
            ImGui::EndGroup();
            ImGui::SameLine();
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));
            if(ImGui::BeginTable("文件信息", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY, ImVec2(-1, -1))) {
                ImGui::TableSetupColumn("选择", ImGuiTableColumnFlags_WidthFixed, font_size * 2);
                ImGui::TableSetupColumn("文件", ImGuiTableColumnFlags_WidthStretch, font_size * 10);
                ImGui::TableSetupColumn("操作", ImGuiTableColumnFlags_WidthFixed, font_size * 2);
                ImGui::TableHeadersRow();
                for (auto& fileinfo : fileinfo_list) {
                    ImGui::TableNextColumn();
                    ImGui::Checkbox(format("##{}", fileinfo.filename).c_str(), &fileinfo.is_checked);
                    ImGui::TableNextColumn();
                    if(fileinfo.is_directory) {
                        ImGui::TextColored(Style::PrimaryColor, "[目录] %s", fileinfo.filename.c_str());
                        ImGui::TableNextColumn();
                        if(ImGui::Button(std::format("进入##{}", fileinfo.filename).c_str())) {
                            current_path.append(fileinfo.filename);
                            str tmp = current_path.string();
                            UpdateFileInfo(tmp);
                        }
                    } else {
                        ImGui::Text("[文件] %s", fileinfo.filename.c_str());
                        ImGui::TableNextColumn();
                    }
                }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar();
            ImGui::EndGroup();
            ImGui::EndPopup();
        }
        if (state == START) {
            ImGui::OpenPopup("文件选择##FileDialog");
            state = RUNNING;
        }
    }

    str FileDialog::GetFileName() {
        if(fileinfo_list.empty()) {
            return "";
        } else {
            for (auto fileinfo : fileinfo_list) {
                if(fileinfo.is_checked) {
                    return fileinfo_list.begin()->filename;
                }
            }
            return "";
        }
    }
}
