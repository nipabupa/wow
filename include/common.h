/*********************************
 *
 * 公共功能
 *
 *********************************/
#pragma once
#include "spdlog/spdlog.h"

// 全局日志记录器
extern std::shared_ptr<spdlog::logger> logger;
// 初始化日志记录器
void InitLogger();


//----------------------------
// (可选) Shell命令
//----------------------------
enum CommandCode {
    NONE = 0,
    RUNNING,
    SUCCESS,
    ERROR,
};

// 单次执行代返回的指令
class Command {
private:
    void _Internal();
public:
    CommandCode code;
    const char* cmd;
    std::string output;
    Command(const char* cmd);
    void Run();
    void Wait();
};

// 后台持续返回的指令
class BackendCommand {
private:
    void _Internal();
public:
    CommandCode code;
    const char* cmd;
    std::string output;
    BackendCommand(const char* cmd);
    void Start();
    void Stop();
};

//----------------------------
// (可选) Socket操作
//----------------------------


//----------------------------
// (可选) 串口操作
//----------------------------
