// 公共日志对象
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/rotating_file_sink.h"
// 全局日志记录器
std::shared_ptr<spdlog::logger> _logger;

void Logger::InitLogger() {
    spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
    // 5MB, Max 5
    _logger = spdlog::rotating_logger_mt("wow_logger", "wow.txt", 1048576 * 5, 5);
    // 设置日志格式
}
