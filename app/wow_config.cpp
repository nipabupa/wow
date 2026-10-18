#include "wow_config.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


WowConfig::WowConfig() {

}

void WowConfig::Load() {
    std::ifstream f("config/app.json");
    json obj = json::parse(f);

    width_ = obj.at("width");
    height_ = obj.at("height");
    fontBase_ = obj.at("font_base");

    logEnabled_ = obj.at("log_enabled");
    if(logEnabled_) {
        logPath_ = obj.at("log_path");
        logSize_ = obj.at("log_size");
        logNum_ = obj.at("log_num");
    }

    forceClose_ = obj.at("force_close");
}
