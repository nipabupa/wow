#pragma once
#include <atomic>
#include <list>
#include <string>
#include <thread>

// 自定义睡眠
#define SLEEP(n) std::this_thread::sleep_for(std::chrono::milliseconds(n))

class WowThread {
    public:
        std::string name;
        WowThread();
        bool isRunning();
        void stop();
        void sendToUi();

    protected:
        void run();

    private:
        std::atomic_bool running = false;
        std::thread* t;
        void exec();
};
