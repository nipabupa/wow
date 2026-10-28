#include "wow_dialog.h"
#include "imgui.h"
#include <list>
#include <string>


WowFileDialog::WowFileDialog() {

}

void WowFileDialog::show() {
    static bool isOpen = true;
    if(running_) {
        isOpen = true;
        ImGui::OpenPopup("WowFileDialog");
    }
    if(ImGui::BeginPopupModal("WowFileDialog", &isOpen, ImGuiWindowFlags_NoCollapse)) {
        ImGui::EndPopup();
    }
}


void WowFileDialog::open(bool is_dir, bool multi) {
    running_ = true;
}

std::string WowFileDialog::getResult() {
    return "";
}

std::list<std::string> WowFileDialog::getResults() {
    return results_;
}
