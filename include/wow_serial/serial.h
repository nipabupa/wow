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
