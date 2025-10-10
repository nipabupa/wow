#include "common.h"

// 公共日志对象
Logger logger;

#ifdef WOW_LOG
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

void Logger::Info(string msg) {
    _logger->info(msg);
}

void Logger::Warn(string msg) {
    _logger->warn(msg);
}

void Logger::Error(string msg) {
    _logger->error(msg);

}
#else
#include <chrono>
void Logger::InitLogger() {}

void Logger::Info(string msg) {
    cout << std::chrono::system_clock::now().time_since_epoch() << " - Info - " << msg << endl;
}

void Logger::Warn(string msg) {
    cout << std::chrono::system_clock::now().time_since_epoch() << " - Warn - " << msg << endl;
}

void Logger::Error(string msg) {
    cout << std::chrono::system_clock::now().time_since_epoch() << " - Error - " << msg << endl;
}
#endif
