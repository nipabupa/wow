#pragma once
#include "spdlog/logger.h"
#include <exception>
#include <vector>

#ifdef WIN32
#ifdef WOW_EXPORT
#define WOW_API __declspec(dllexport)
#else
#define WOW_API __declspec(dllimport)
#endif
#else
#define WOW_API
#endif

class WowException : public std::exception {
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
    extern WOW_API std::shared_ptr<spdlog::logger> logger;
    void InitConsoleLogger();
    void InitFileLogger(std::string log_path);
}

// 自定义睡眠
#define SLEEP(n) std::this_thread::sleep_for(std::chrono::milliseconds(n))

namespace WowUtils {
    // 字符串分割
    std::vector<std::string> StringSplit(std::string s, char deli);
    // 获取当前日期字符串
    std::string GetCurrentDateTime();
}
