//----------------------------
// (可选) Shell操作
//----------------------------
#include <thread>
#include <chrono>
#ifdef WIN32
#include <windows.h>
#endif
#include "common.h"

#ifdef WOW_SHELL

void Command::_Internal() {
#ifdef WIN32
    FILE* pipe = _popen(cmd, "r");
#else
    FILE* pipe = popen(cmd, "r");
#endif
    if(!pipe) {
        code = FAILED;
        return;
    }
    std::ostringstream ss;
    char buffer[256];
    while(fgets(buffer, 256, pipe) != NULL) {
        ss << buffer;
    }
    pclose(pipe);
    output = ss.str();
    code = SUCCESS;
}

Command::Command(const char* cmd) {
    this->cmd = cmd;
    code = NONE;
}

string Command::Run() {
    code = NONE;
    std::thread t(&Command::_Internal, this);
    t.detach();
    while(code == RUNNING) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return output;
}

BackendCommand::BackendCommand(const char* cmd) {
    this->cmd = cmd;
    code = NONE;
}

void BackendCommand::_Internal() {
#ifdef WIN32
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    HANDLE hRead, hWrite;
    CreatePipe(&hRead, &hWrite, &sa, 0);
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = hRead;
    si.hStdOutput = hWrite;
    si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    BOOL result = CreateProcessA(NULL, (LPSTR)this->cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if (!result) {
        return -1;
    }
#else
#endif
}

void BackendCommand::Start() {

}

void BackendCommand::Stop() {

}
#endif
