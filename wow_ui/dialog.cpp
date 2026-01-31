#include "wow_common.h"
#include <format>
#ifdef WIN32
#include <windows.h>
#include <shlobj.h>
#endif
#include "imgui.h"
#include "imgui_extends.h"
#include "imgui_stdlib.h"
#include "wow_ui.h"


namespace WowDialog {
    void BackendLoading::Display() {
        if(state == RUNNING) {
            auto font_size = ImGui::GetFontSize();
            auto style = ImGui::GetStyle();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(font_size / 2, 0));
            ImGui::Begin("Loading", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
            ImGui::Spinner("Spinner", font_size, font_size / 2, ImGui::GetExtendStyle().LoadingColor.vec4);
            ImGui::SetWindowPos(ImVec2(WowConfig::app_info.width - ImGui::GetWindowSize().x - style.WindowPadding.x, style.WindowPadding.y));
            ImGui::End();
            ImGui::PopStyleVar();
        }
    }

    void GlobalLoading::Display() {
        if(state == READY || message_dialog.IsRunning() || file_dialog.IsRunning()) {
            return;
        }
        auto font_size = ImGui::GetFontSize();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(font_size / 2, 0));
        if(ImGui::BeginPopupModal("GlobalLoading", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Spinner("Spinner", font_size, font_size / 2, ImGui::GetExtendStyle().LoadingColor.vec4);
            ImGui::SetWindowPos(ImVec2((WowConfig::app_info.width - ImGui::GetWindowSize().x) / 2, font_size * 20));
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
        if(state == READY) {
            return;
        }
        auto style = ImGui::GetStyle();
        auto font_size = ImGui::GetFontSize();
        if(ImGui::BeginPopupModal("注意##MessageDialog", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::SetWindowPos(ImVec2((WowConfig::app_info.width - ImGui::GetWindowSize().x) / 2, font_size * 10));
            ImGui::Text("%s", message.c_str());
            ImGui::BeginGroup();
            if(ImGui::Button("确定", ImVec2(font_size * 6, 0))){
                if(confirm != NULL) {
                    confirm();
                    confirm = NULL;
                }
                ImGui::CloseCurrentPopup();
                state = READY;
            };
            if(confirm != NULL) {
                ImGui::SameLine();
                if(ImGui::Button("取消", ImVec2(font_size * 6, 0))){
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
        update = true;
#ifdef WIN32
        char buffer[256];
        DWORD a = 255;
        if(GetUserNameA(buffer, &a)) {
            const_directory.push_back({"桌面", std::format("C:\\Users\\{}\\Desktop", buffer)});
        }
        DWORD length = GetLogicalDriveStringsA(255, buffer);
        for(size_t i=0; i<length; i++) {
            if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
                auto tmp = std::format("{}:\\", buffer[i]);
                const_directory.push_back({tmp, tmp});
            }
        }
#else
        auto home = std::getenv("HOME");
        if(strlen(home) != 0) {
            const_directory.push_back({"Home", home});
            auto lang = std::string(std::getenv("LANG"));
            if(lang.starts_with("zh_CN")) {
                const_directory.push_back({"桌面", std::format("{}/桌面", home)});
            } else {
                const_directory.push_back({"Desktop", std::format("{}/Desktop", home)});
            }
        }
#endif
    }

    void FileDialog::Open() {
        state = START;
        update = true;
    }

    void FileDialog::Wait() {
        do {
            SLEEP(50);
        } while(state == RUNNING);
    }

    void FileDialog::ChangeToSelectFiles(std::list<std::string>&& filters) {
        exts.clear();
        exts.splice(exts.end(), filters);
        is_select_directory = false;
        is_save_file = false;
    }

    void FileDialog::ChangeToSelectDirectory() {
        is_select_directory = true;
        is_save_file = false;
    }

    void FileDialog::ChangeToSaveFile(std::list<std::string>&& filters) {
        exts.clear();
        exts.splice(exts.end(), filters);
        is_select_directory = true;
        is_save_file = true;
    }

    void FileDialog::UpdateFileInfo() {
        fileinfo_list.clear();
        for (const auto& entry : std::filesystem::directory_iterator(current_path)) {
            if(is_select_directory && !entry.is_directory()) {
                continue;
            }
            if(!entry.is_directory() && !exts.empty()) {
                bool flag = false;
                for (auto filter : exts) {
                    if(entry.path().filename().string().ends_with(filter)) {
                        flag = true;
                    }
                }
                if(!flag) {
                    continue;
                }
            }
            FileInfo tmp;
            tmp.path = entry.path();
            tmp.filename = (char*)entry.path().filename().generic_u8string().c_str();
            tmp.is_checked = false;
            tmp.is_directory = entry.is_directory();
            fileinfo_list.push_back(tmp);
        }
        fileinfo_list.sort(_compare);
    }

    void FileDialog::Display() {
        auto style = ImGui::GetExtendStyle();
        if(state == READY || message_dialog.IsRunning()) {
            return;
        }
        if(update) {
            if(current_name.empty() && const_directory.size() > 0) {
                current_path = const_directory.front().second;
            }
            UpdateFileInfo();
            update = false;
        }
        auto font_size = ImGui::GetFontSize();
        ImVec2 button_size = ImVec2(font_size * 6, 0);
        if(ImGui::BeginPopupModal("文件选择##FileDialog", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize)) {
            ImGui::SetWindowSize(ImVec2(font_size*70, font_size*35));
            // 当前目录
            ImGui::BeginGroup();
            if(ImGui::PrimaryButton("确定##FileDialog", button_size)) {
                state = READY;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if(ImGui::Button("取消##FileDialog", button_size)) {
                fileinfo_list.clear();
                state = READY;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if(ImGui::Button("上一级##FileDialog", button_size)) {
                current_path = current_path.parent_path();
                current_name = (char*)current_path.filename().generic_u8string().c_str();
                update = true;
            }
            ImGui::SameLine();
            ImGui::PushItemWidth(font_size*30);
            ImGui::InputText("当前目录", &current_name);
            ImGui::PopItemWidth();
            ImGui::EndGroup();
            // 输入
            if(is_save_file) {
                ImGui::PushItemWidth(font_size*40);
                ImGui::InputText("输入文件名##FileDialog", input_filename, 256);
                ImGui::PopItemWidth();
            }
            // 内容
            ImGui::BeginGroup();
            ImGui::BeginGroup();
            for(auto p : const_directory) {
                if(ImGui::Button(std::format("{}##FileDialog", p.first).c_str(), button_size)) {
                    current_path = p.second;
                    current_name = (char*)current_path.filename().generic_u8string().c_str();
                    update = true;
                };
            }
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
                        ImGui::TextColored(style.PrimaryColor.vec4, "%s", fileinfo.filename.c_str());
                        ImGui::TableNextColumn();
                        if(ImGui::ArrowButton(std::format("##Right{}", fileinfo.filename).c_str(), ImGuiDir_Right)) {
                            current_path = fileinfo.path;
                            current_name = (char*)current_path.filename().generic_u8string().c_str();
                            update = true;
                        }
                    } else {
                        ImGui::Text("%s", fileinfo.filename.c_str());
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

    fs::path FileDialog::GetFileName() {
        if(fileinfo_list.empty()) {
            return "";
        } else {
            for (auto fileinfo : fileinfo_list) {
                if(!fileinfo.is_directory && fileinfo.is_checked) {
                    return fileinfo.path;
                }
            }
            return "";
        }
    }

    std::list<fs::path> FileDialog::GetFileNames() {
        std::list<fs::path> res;
        if(fileinfo_list.empty()) {
            return res;
        } else {
            for (auto fileinfo : fileinfo_list) {
                if(!fileinfo.is_directory && fileinfo.is_checked) {
                    res.push_back(fileinfo.path);
                }
            }
            return res;
        }
    }

    fs::path FileDialog::GetSaveName() {
        if(current_path.empty()) {
            return "";
        } else {
            fs::path tmp = current_path;
            tmp.append(input_filename);
            return tmp;
        }
    }

    fs::path FileDialog::GetDirName() {
        for (auto fileinfo : fileinfo_list) {
            if(fileinfo.is_directory && fileinfo.is_checked) {
                return fileinfo.path;
            }
        }
        return current_path;
    }
}
