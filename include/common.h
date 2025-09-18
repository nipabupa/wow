#include "spdlog/spdlog.h"

// 全局日志记录器
extern std::shared_ptr<spdlog::logger> logger;

// 初始化日志记录器
void InitLogger();

// 文件管理器
namespace FileManager {
    // 选择单个文件
    void SelectFile(char* filename);
    // 选择多个文件
    void SelectFiles();
    // 选择目录
    void SelectDirectory(char* dirname);
    // 保存文件
    void SaveFile(char* filename);
}
