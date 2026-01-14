#include <string>
#include <functional>

//----------------------------
// 任务管理
//----------------------------
namespace WowTask {
    class TaskResult {
        // 任务结果
        bool state;
        // 任务结束提示
        std::string *message;
        TaskResult(bool result, std::string* msg = nullptr);
        ~TaskResult();
    };
    // 初始化全局任务线程
    void InitGlobalTaskThread();
    // 初始化后台任务线程
    void InitBackendTaskThread();
    // 关闭全局任务线程
    void InitGlobalTaskThread();
    // 关闭后台任务线程
    void InitBackendTaskThread();
    // 创建全局任务
    void CreateGlobalTask(std::function<TaskResult()> task);
    // 创建后台任务
    void CreateBackendTask(std::function<TaskResult()> task);
}
