#include "spdlog/spdlog.h"
#include "imgui.h"
#include "imfilebrowser.h"
#include <string>
#include <vector>

// 全局日志记录器
extern std::shared_ptr<spdlog::logger> logger;
extern ImGui::FileBrowser fileDialog;

// 初始化日志记录器
void InitLogger();

// 文件管理器
namespace FileManager {
    // 选择单个文件
    std::string SelectFile();
    // 选择多个文件
    std::vector<std::string> SelectFiles();
    // 选择目录
    std::string SelectDirectory();
    // 保存文件
    std::string SaveFile();
    // 获取
    std::string GetFileName();
}
