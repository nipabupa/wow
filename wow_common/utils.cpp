#include "wow_common.h"
#include <chrono>
#include <format>
#include <sstream>


namespace WowUtils {
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
