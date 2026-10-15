#pragma once
#include <exception>
#include <string>
#include <vector>
#include "spdlog/spdlog.h"


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

namespace WowUtils {
    std::shared_ptr<spdlog::logger> InitConsoleLogger();
    std::shared_ptr<spdlog::logger> InitFileLogger(std::string log_path, unsigned int max_size, unsigned int max_num);
    // 字符串分割
    std::vector<std::string> StringSplit(std::string& s, char deli);
    // 获取当前日期字符串
    std::string GetCurrentDateTime(char type = 'f');
}
