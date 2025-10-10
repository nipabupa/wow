/*********************************
 *
 * 公共功能
 *
 *********************************/
#pragma once
#include "stl.h"
//----------------------------
// (可选) 日志
//----------------------------
class Logger {
public:
    // 初始化日志记录器
    void InitLogger();
    void Info(string msg);
    void Warn(string msg);
    void Error(string msg);
};
extern Logger logger;
//----------------------------
// (可选) Shell命令
//----------------------------
#ifdef WOW_SHELL
enum CommandCode {
    NONE = 0,
    RUNNING,
    SUCCESS,
    FAILED
};

// 单次执行代返回的指令
class Command {
private:
    void _Internal();
    const char* cmd;
    CommandCode code;
    string output;
public:
    Command(const char* cmd);
    string Run();
};

// 后台持续返回的指令
class BackendCommand {
private:
    void _Internal();
public:
    CommandCode code;
    const char* cmd;
    BackendCommand(const char* cmd);
    void Start();
    void Stop();
};
#endif
//----------------------------
// (可选) Socket操作
//----------------------------
#ifdef WOW_SOCKET
#ifdef WIN32
#include "winsock2.h"
#include <mutex>
class SocketClient {
private:
    string ip;
    unsigned short port;
    SOCKET client;
    bool running;
public:
    SocketClient(string ip, unsigned short port);
    void Open();
    void Close();
    void Send(string msg);
    string ReceiveMessage();
    void StartReceive(list<string>& data, std::mutex& mtx);
    void StopReceive();
};
#else
#endif
#endif
//----------------------------
// (可选) 串口操作
//----------------------------
#ifdef WOW_SERIAL
#include <mutex>
class SerialClient {
private:
    unsigned short number;
    bool running;
public:
    SerialClient(unsigned short number) {
        this->number = number;
    }
    void Open();
    void Close();
    void Send(string msg);
    string ReceiveMessage();
    void StartReceive(list<string>& data, std::mutex& mtx);
    void StopReceive();
};
#endif
