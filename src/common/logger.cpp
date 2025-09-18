#include "common.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/rotating_file_sink.h"


std::shared_ptr<spdlog::logger> logger;


void InitLogger() {
    spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
    // 5MB, Max 5
    logger = spdlog::rotating_logger_mt("wow_logger", "wow.txt", 1048576 * 5, 5);
    // 设置日志格式
}
