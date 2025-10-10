#include <format>
#include <thread>
#include "stl.h"
#include "wow.h"
#include "common.h"


namespace App {
    void InnerBackendTask(const string& title, function<void()> task) {
        try {
            task();
        } catch (exception& e) {
            logger.Error(e.what());
            message_dialog.Open(format("{}失败", title));
        }
        backend_loading.Stop();
    }

    void InnerGlobalTask(const string& title, function<void()> task) {
        try {
            task();
        } catch (exception& e) {
            logger.Error(e.what());
            message_dialog.Open(format("{}失败", title));
        }
        global_loading.Stop();
    }

    void CreateBackendTask(const string& title, function<void()> task) {
        if(backend_loading.IsRunning() || global_loading.IsRunning()) {
            message_dialog.Open("任务正在运行, 请稍候");
            return;
        }
        backend_loading.Start();
        std::thread t(std::bind(InnerBackendTask, title, task));
        t.detach();
    }

    void CreateGlobalTask(const string& title, function<void()> task) {
        if(App::backend_loading.IsRunning() || App::global_loading.IsRunning()) {
            message_dialog.Open("任务正在运行, 请稍候");
            return;
        }
        global_loading.Start();
        std::thread t(std::bind(InnerGlobalTask, title, task));
        t.detach();
    }
}
