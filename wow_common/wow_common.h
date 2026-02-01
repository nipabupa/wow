#pragma once
#include <exception>
#include <vector>
#include "spdlog/logger.h"

#ifdef WIN32
#ifdef WOW_COMMON_EXPORT
#define WOW_COMMON_API __declspec(dllexport)
#else
#define WOW_COMMON_API __declspec(dllimport)
#endif
#else
#define WOW_COMMON_API __attribute__((visibility("default")))
#endif

class WOW_COMMON_API WowException : public std::exception {
private:
    std::string msg;
public:
    WowException(const std::string& msg) {
        this->msg = msg;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

namespace WowCommon {
    extern WOW_COMMON_API std::shared_ptr<spdlog::logger> logger;
    WOW_COMMON_API void InitConsoleLogger();
    WOW_COMMON_API void InitFileLogger(std::string log_path, unsigned int max_size, unsigned int max_num);
}

// 自定义睡眠
#define SLEEP(n) std::this_thread::sleep_for(std::chrono::milliseconds(n))

namespace WowUtils {
    // 字符串分割
    WOW_COMMON_API std::vector<std::string> StringSplit(std::string& s, char deli);
    // 获取当前日期字符串
    WOW_COMMON_API std::string GetCurrentDateTime(char type = 'f');
}
