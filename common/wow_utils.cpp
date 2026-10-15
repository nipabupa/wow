#include "wow_common.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include <chrono>
#include <format>
#include <sstream>


namespace WowUtils {
    std::shared_ptr<spdlog::logger> InitFileLogger(std::string log_path, unsigned int max_size, unsigned int max_num) {
        spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
        std::shared_ptr<spdlog::logger> logger = spdlog::rotating_logger_mt("wow_logger", log_path, max_size, max_num);
        logger->flush_on(spdlog::level::warn);
        return logger;
    }

    std::shared_ptr<spdlog::logger> InitConsoleLogger() {
        spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
        std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("wow_logger");
        logger->flush_on(spdlog::level::warn);
        return logger;
    }


    std::vector<std::string> StringSplit(std::string &s, char deli) {
        std::vector<std::string> res;
        std::istringstream ss(s);
        std::string token;
        while(std::getline(ss, token, deli)) {
            res.push_back(token);
        }
        return res;
    }

    std::string GetCurrentDateTime(char type) {
        auto now = std::chrono::system_clock::now();
        if(type == 'f') {
            // 文件名字符串
            return std::format("{:%Y_%m_%d_%H_%M_%S}", now);
        } else if(type == 'm') {
            // 显示字符串-毫秒
            auto total_mil = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() & 0b111;
            return std::format("{:%Y-%m-%d %H:%M:%S}.{}", now, total_mil);
        } else if(type == 's') {
            // 显示字符串-秒
            return std::format("{:%Y-%m-%d %H:%M:%S}", now);
        } else {
            throw WowException("未知的时间类型");
        }
    }
}
