#include "spdlog/spdlog.h"
#include <string>
#include <vector>

// 全局日志记录器
extern std::shared_ptr<spdlog::logger> logger;

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
}
