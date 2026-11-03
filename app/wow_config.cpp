#include "wow_config.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <exception>

using json = nlohmann::json;


WowConfig::WowConfig() {

}

void WowConfig::Load() {
    try {
        std::ifstream f("config/app.json");
        json obj = json::parse(f);
        width_ = obj.at("width");
        height_ = obj.at("height");

        logEnabled_ = obj.at("log_enabled");
        if(logEnabled_) {
            logPath_ = obj.at("log_path");
            logSize_ = obj.at("log_size");
            logNum_ = obj.at("log_num");
        }

        forceClose_ = obj.at("force_close");
    } catch (std::exception &e) {
        // 配置异常时使用默认值
        width_ = 1280;
        height_ = 720;
        logEnabled_ = false;
        forceClose_ = false;
    }

    // 检查字体
    if(!std::filesystem::is_regular_file(baseFontPath_)) {
#ifdef _WIN32
        baseFontPath_ = "C:\\Windows\\Fonts\\Deng.ttc";
#else
        baseFontPath_ = "/usr/share/fonts/noto-cjk/NotoSansCJK-Medium.ttc";
#endif
    }

    if(!std::filesystem::is_regular_file(iconFontPath_)) {
#ifdef _WIN32
        iconFontPath_ = "C:\\Windows\\Fonts\\Deng.ttc";
#else
        iconFontPath_ = "/usr/share/fonts/TTF/MesloLGSNerdFont-Regular.ttf";
#endif
    }
}
