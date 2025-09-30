#include <chrono>
#include <sstream>
#include <thread>


class Command {
private:
    void _Internal() {
        FILE* pipe = popen(cmd, "r");
        if(!pipe) {
            code = ERROR;
            return;
        }
        std::ostringstream ss;
        char buffer[1024];
        while(fgets(buffer, 1024, pipe) != NULL) {
            ss << buffer;
        }
        pclose(pipe);
        code = SUCCESS;
        output = ss.str();
    }
public:
    CommandCode code;
    const char* cmd;
    std::string output;
    Command(const char* cmd) {
        this->cmd = cmd;
        code = NONE;
    }

    void Run() {
        code = NONE;
        std::thread t(&Command::_Internal, this);
        t.detach();
    }

    void Wait() {
        while(code == RUNNING) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};
