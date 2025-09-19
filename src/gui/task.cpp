#include <exception>
#include <format>
#include <functional>
#include <thread>
#include "gui.h"
#include "common.h"


namespace TaskManager {
    void InnerBackendTask(const char* title, std::function<void()> task) {
        try {
            task();
        } catch (std::exception& e) {
            logger->error(e.what());
            Message(std::format("{}失败", title));
        }
        State::backend_task_state = State::READY;
    }

    void InnerGlobalTask(const char* title, std::function<void()> task) {
        try {
            task();
        } catch (std::exception& e) {
            logger->error(e.what());
            Message(std::format("{}失败", title));
        }
        State::global_task_state = State::STOP;
    }

    void Message(std::string msg, std::function<void()> task) {
        State::global_msg_state = State::START;
        State::msg = msg;
        State::confirm = task;
    }

    void CreateBackendTask(const char* title, std::function<void()> task) {
        State::backend_task_state = State::RUNNING;
        std::thread t(std::bind(InnerBackendTask, title, task));
        t.detach();
    }

    void CreateGlobalTask(const char* title, std::function<void()> task) {
        State::global_task_state = State::START;
        std::thread t(std::bind(InnerGlobalTask, title, task));
        t.detach();
    }
}
