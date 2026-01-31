// 公共日志对象
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "wow_common.h"


namespace WowCommon {
    WOW_COMMON_API std::shared_ptr<spdlog::logger> logger;

    WOW_COMMON_API void InitFileLogger(std::string log_path, unsigned int max_size, unsigned int max_num) {
        spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
        logger = spdlog::rotating_logger_mt("wow_logger", log_path, max_size, max_num);
        logger->flush_on(spdlog::level::warn);
    }

    WOW_COMMON_API void InitConsoleLogger() {
        spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
        logger = spdlog::stdout_color_mt("wow_logger");
        logger->flush_on(spdlog::level::warn);
    }
}
