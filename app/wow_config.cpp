#include "wow_config.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


WowConfig::WowConfig() {
}

void WowConfig::Load() {
    std::ifstream f("config/app.json");
    json obj = json::parse(f);

    width = obj.at("width");
    height = obj.at("height");
    font_base = obj.at("font_base");

    log_enabled = obj.at("log_enabled");
    if(log_enabled) {
        log_path = obj.at("log_path");
        log_size = obj.at("log_size");
        log_num = obj.at("log_num");
    }

    force_close = obj.at("force_close");
}
