#include <thread>
#include "wow_common.h"
#include "wow_ui.h"


namespace WowTask {
    static std::function<TaskResult()> global_task;
    static std::function<TaskResult()> backend_task;
    static std::thread* global_task_thread = nullptr;
    static std::thread* backend_task_thread = nullptr;
    static bool is_global_thread_running;
    static bool is_backend_thread_running;

    void _GlobalTaskThread() {
        while(is_global_thread_running) {
            if(global_task == nullptr) {
                SLEEP(50);
                continue;
            }
            WowDialog::global_loading.Start();
            auto result = global_task();
            WowDialog::global_loading.Stop();
            if(!result.message.empty()) {
                WowDialog::message_dialog.Open(result.message);
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
            auto result = backend_task();
            WowDialog::backend_loading.Stop();
            if(!result.message.empty()) {
                WowDialog::message_dialog.Open(result.message);
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
    void CreateGlobalTask(std::function<TaskResult()> task) {
        global_task = task;
    }
    // 创建后台任务
    void CreateBackendTask(std::function<TaskResult()> task) {
        if(global_task != nullptr) {
            return;
        }
        backend_task = task;
    }
}
