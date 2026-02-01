#include <atomic>
#include <thread>
#include "wow_common.h"
#include "wow_ui.h"


namespace WowTask {
    // 原子指针赋值确保任务指针正确
    static std::atomic<std::string(*)()> global_task;
    static std::atomic<std::string(*)()> backend_task;
    static std::thread* global_task_thread = nullptr;
    static std::thread* backend_task_thread = nullptr;
    // 工作线程仅读取状态，无需加锁或原子状态
    static bool is_global_thread_running;
    static bool is_backend_thread_running;

    void _GlobalTaskThread() {
        while(is_global_thread_running) {
            if(global_task == nullptr) {
                SLEEP(50);
                continue;
            }
            WowDialog::global_loading.Start();
            auto result = global_task.load()();
            WowDialog::global_loading.Stop();
            if(!result.empty()) {
                WowDialog::message_dialog.Open(result.c_str());
            }
            global_task = nullptr;
        }
    }

    void _BackendTaskThread() {
        while(is_backend_thread_running) {
            if(backend_task == nullptr) {
                SLEEP(50);
                continue;
            }
            WowDialog::backend_loading.Start();
            auto result = backend_task.load()();
            WowDialog::backend_loading.Stop();
            if(!result.empty()) {
                WowDialog::message_dialog.Open(result);
            }
            backend_task = nullptr;
        }
    }

    // 初始化全局任务线程
    void InitGlobalTaskThread() {
        is_global_thread_running = true;
        global_task_thread = new std::thread(_GlobalTaskThread);
        global_task_thread->detach();
    }
    // 初始化后台任务线程
    void InitBackendTaskThread() {
        is_backend_thread_running = true;
        backend_task_thread = new std::thread(_BackendTaskThread);
        backend_task_thread->detach();
    }
    // 关闭全局任务线程
    void ReleaseGlobalTaskThread() {
        is_global_thread_running = false;
    }
    // 关闭后台任务线程
    void ReleaseBackendTaskThread() {
        is_backend_thread_running = false;
    }
    // 创建全局任务
    WOW_UI_API void CreateGlobalTask(std::string(*task)()) {
        if(global_task != nullptr) {
            WowDialog::message_dialog.Open("任务正在运行");
            return;
        }
        global_task = task;
    }
    // 创建后台任务
    WOW_UI_API void CreateBackendTask(std::string(*task)()) {
        if(global_task != nullptr) {
            WowDialog::message_dialog.Open("任务正在运行");
            return;
        }
        backend_task = task;
    }

    WOW_UI_API bool IsTaskRunning() {
        return global_task!= nullptr || backend_task != nullptr;
    }

    WOW_UI_API bool IsGlobalTaskRunning() {
        return global_task!= nullptr;
    }

    WOW_UI_API bool IsBackendTaskRunning() {
        return backend_task != nullptr;
    }
}
