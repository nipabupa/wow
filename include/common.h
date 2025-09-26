#ifndef WOW_COMMON
#define WOW_COMMON 1
#include "spdlog/spdlog.h"

// 全局日志记录器
extern std::shared_ptr<spdlog::logger> logger;

// 初始化日志记录器
void InitLogger();
#endif
