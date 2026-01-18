#include <queue>
#include <thread>
#include <mutex>
#include "wow_common.h"
#include "wow_ui.h"


namespace WowTask {
    static std::queue<std::function<TaskResult()>> global_task_queue;
    static std::queue<std::function<TaskResult()>> backend_task_queue;
    static std::thread* global_task_thread = nullptr;
    static std::thread* backend_task_thread = nullptr;
    static bool is_global_thread_running;
    static bool is_backend_thread_running;
    static bool is_global_running;
    static bool is_backend_running;
    static std::mutex global_mutex;
    static std::mutex backend_mutex;

    void _GlobalTaskThread() {
        while(is_global_thread_running) {
            if(global_task_queue.empty()) {
                SLEEP(50);
                continue;
            }
            auto task = global_task_queue.front();
            global_mutex.lock();
            global_task_queue.pop();
            global_mutex.unlock();
            WowDialog::global_loading.Start();
            is_global_running = true;
            auto result = task();
            is_global_running = false;
            WowDialog::global_loading.Stop();
            if(!result.state) {
                WowDialog::message_dialog.Open(std::format("任务执行失败: {}", result.message));
            } else {
                if(result.message.size() != 0) {
                    WowDialog::message_dialog.Open(result.message);
                }
            }
        }
    }

    void _BackendTaskThread() {
        while(is_backend_thread_running) {
            if(backend_task_queue.empty()) {
                SLEEP(50);
                continue;
            }
            auto task = backend_task_queue.front();
            backend_mutex.lock();
            backend_task_queue.pop();
            backend_mutex.unlock();
            WowDialog::backend_loading.Start();
            is_backend_running = true;
            auto result = task();
            is_backend_running = false;
            WowDialog::backend_loading.Stop();
            if(!result.state) {
                WowDialog::message_dialog.Open(std::format("任务执行失败: {}", result.message));
            } else {
                if(result.message.size() != 0) {
                    WowDialog::message_dialog.Open(result.message);
                }
            }
        }
    }

    // 初始化全局任务线程
    void InitGlobalTaskThread() {
        global_task_thread = new std::thread(_GlobalTaskThread);
        global_task_thread->detach();
    }
    // 初始化后台任务线程
    void InitBackendTaskThread() {
        backend_task_thread = new std::thread(_BackendTaskThread);
        backend_task_thread->detach();
    }
    // 关闭全局任务线程
    void ReleaseGlobalTaskThread() {
        is_global_thread_running = false;
        global_task_thread->join();
        delete global_task_thread;
    }
    // 关闭后台任务线程
    void ReleaseBackendTaskThread() {
        is_backend_thread_running = false;
        backend_task_thread->join();
        delete backend_task_thread;
    }
    // 创建全局任务
    void CreateGlobalTask(std::function<TaskResult()> task) {
        global_mutex.lock();
        global_task_queue.push(task);
        global_mutex.unlock();
    }
    // 创建后台任务
    void CreateBackendTask(std::function<TaskResult()> task) {
        if(is_global_running) {
            return;
        }
        backend_mutex.lock();
        backend_task_queue.push(task);
        backend_mutex.unlock();
    }
}
