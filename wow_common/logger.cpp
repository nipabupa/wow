// 公共日志对象
#include "spdlog/common.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"
#include "wow_common.h"


namespace WowCommon {
    std::shared_ptr<spdlog::logger> logger;

    void InitFileLogger(std::string log_path, unsigned int max_size, unsigned int max_num) {
        spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
        logger = spdlog::rotating_logger_mt("wow_logger", log_path, max_size, max_num);
        logger->flush_on(spdlog::level::warn);
    }

    void InitConsoleLogger() {
        spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
        logger = spdlog::get("console");
        logger->flush_on(spdlog::level::warn);
    }
}
