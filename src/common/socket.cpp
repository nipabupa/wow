//----------------------------
// (可选) Socket操作
//----------------------------
#include "common.h"
#include <format>
#ifdef WOW_SOCKET
#ifdef WIN32
#pragma comment(lib, "WS2_32")

SocketClient::SocketClient(string ip, unsigned short port) {
    this->ip = ip;
    this->port = port;
    this->running = false;
    // 初始化DLL
    WSADATA wsdata;
    WSAStartup(MAKEWORD(2, 2), &wsdata);
    this->client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void SocketClient::Open() {
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(this->ip.c_str());
    sockAddr.sin_port = htons(this->port);
    if(connect(client, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        logger.Error(std::format("SocketClient connect error: {}", WSAGetLastError()));
    }
}

void SocketClient::Close() {
    running = false;
    //关闭套接字
    closesocket(client);
    //终止使用 DLL
    WSACleanup();
}

void SocketClient::Send(string msg) {
    int v = send(client, msg.c_str(), msg.length() + 1, 0); 
    if(v == 0) {
        logger.Warn("SocketClient socket has been closed");
    } else if (v < 0) {
        logger.Error(std::format("SocketClient send error: {}", WSAGetLastError()));
    }
}

string SocketClient::ReceiveMessage() {
    char szBuffer[MAXBYTE] = {0};
    int v = recv(client, szBuffer, MAXBYTE, 0);
    if(v > 0) {
        return string(szBuffer);
    } else {
        return "";
    }
}

void SocketClient::StartReceive(list<string>& data, std::mutex& mtx) {
    running = true;
    char szBuffer[MAXBYTE] = {0};
    while(running) {
        int v = recv(client, szBuffer, MAXBYTE, 0);
        if(v == 0) {
            logger.Warn("SocketClient socket has been closed");
        } else if (v < 0) {
            logger.Error(std::format("SocketClient recv error: {}", WSAGetLastError()));
        } else {
            mtx.lock();
            data.push_back(string(szBuffer));
            mtx.unlock();
        }
    }
}

void SocketClient::StopReceive() {
    running = false;
}
#elif

#endif
#endif
