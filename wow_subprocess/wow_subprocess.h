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
