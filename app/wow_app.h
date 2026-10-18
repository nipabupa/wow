#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <queue>
#include <spdlog/logger.h>

#include "wow_theme.h"
#include "wow_config.h"


class WowApp {
    public:
        WowApp();
        void exec();

    protected:
        static WowApp* self;

        WowConfig config_;
        std::shared_ptr<spdlog::logger> logger_;
        WowTheme theme_;
        // UI
        virtual void build();
        // app关闭回调
        virtual bool onClose();
        // app初始化完成UI未渲染前回调
        virtual void onSetup();
    private:
        // UI线程任务队列
        std::queue<std::function<void()>> taskQueue_;
        static void glfwErrorCallback(int error, const char* description);
        static void glfwCloseCallback(GLFWwindow* window);
};


// namespace WowDialog {
//     enum TaskState {
//         READY,
//         START,
//         RUNNING,
//         STOP,
//     };
//     //----------------------------
//     // 后台加载
//     //----------------------------
//     class WOW_UI_API BackendLoading {
//     private:
//         std::atomic<TaskState> state;
//     public:
//         BackendLoading() {
//             state = READY;
//         }
//         void Display();
//         bool IsRunning() {
//             return state == RUNNING;
//         }
//         void Start() {
//             state = RUNNING;
//         }
//         void Stop() {
//             state = READY;
//         }
//     };
//     //----------------------------
//     // 全局加载
//     //----------------------------
//     class WOW_UI_API GlobalLoading {
//     private:
//         std::atomic<TaskState> state;
//     public:
//         GlobalLoading() {
//             state = READY;
//         }
//         void Display();
//         bool IsRunning() {
//             return state == RUNNING;
//         }
//         void Start() {
//             state = START;
//         }
//         void Stop() {
//             state = STOP;
//         }
//     };
//     //----------------------------
//     // 消息通知窗口
//     //----------------------------
//     class WOW_UI_API MessageDialog {
//     private:
//         // 全局消息状态
//         std::atomic<TaskState> state;
//         // 消息窗口内容
//         std::string message;
//         // 消息窗口确认回调
//         std::function<void()> confirm; // 是否点击确认回调
//     public:
//         MessageDialog() {
//             state = READY;
//         }
//         bool IsRunning() {
//             return state == RUNNING;
//         }
//         void Display();
//         void Open(const std::string& msg, std::function<void()> callback = NULL) {
//             message = msg;
//             confirm = callback;
//             state = START;
//         }
//     };
//     //----------------------------
//     // 文件选择窗口
//     //----------------------------
//     struct WOW_UI_API FileInfo {
//         fs::path path;
//         std::string filename;
//         bool is_directory;
//         bool is_checked;
//     };
//     class WOW_UI_API FileDialog {
//     private:
//         std::atomic<TaskState> state;
//         fs::path current_path;
//         std::string current_name;
//         char input_filename[256];
//         bool is_select_directory;
//         bool is_save_file;
//         bool update;
//         short ext_index = 0;
//         std::vector<std::string> exts;
//         std::list<FileInfo> fileinfo_list;
//         std::list<std::pair<std::string, std::string>> const_directory;
//         void UpdateFileInfo();
//     public:
//         FileDialog();
//         bool IsRunning() {
//             return state == RUNNING;
//         }
//         void Display();
//         void Open();
//         void Wait();
//         fs::path GetFileName();
//         std::list<fs::path> GetFileNames();
//         fs::path GetSaveName();
//         fs::path GetDirName();
//         void ChangeToSelectFiles(std::vector<std::string>&& filters);
//         void ChangeToSelectDirectory();
//         void ChangeToSaveFile(std::vector<std::string>&& filters);
//     };
//     extern WOW_UI_API BackendLoading backend_loading;
//     extern WOW_UI_API GlobalLoading global_loading;
//     extern WOW_UI_API MessageDialog message_dialog;
//     extern WOW_UI_API FileDialog file_dialog;
// }
//
// namespace WowTask {
//     // 初始化全局任务线程
//     void InitGlobalTaskThread();
//     // 初始化后台任务线程
//     void InitBackendTaskThread();
//     // 关闭全局任务线程
//     void ReleaseGlobalTaskThread();
//     // 关闭后台任务线程
//     void ReleaseBackendTaskThread();
//     // 是否任务运行
//     WOW_UI_API bool IsBackendTaskRunning();
//     // 是否任务运行
//     WOW_UI_API bool IsGlobalTaskRunning();
//     // 是否任务运行
//     WOW_UI_API bool IsTaskRunning();
//     // 创建全局任务
//     WOW_UI_API void CreateGlobalTask(std::string(*task)());
//     // 创建后台任务
//     WOW_UI_API void CreateBackendTask(std::string(*task)());
// }
//
// // 启动APP
// WOW_UI_API int Run();
