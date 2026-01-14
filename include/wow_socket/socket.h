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
