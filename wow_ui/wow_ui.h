#pragma once
#include <functional>
#include <list>
#include <string>
#include "wow_common.h"


namespace WowConfig {
    struct AppInfo {
        // 设计窗口尺寸
        int width = 1280;
        int height = 768;
        // 基础字体大小
        float font_base = 16.0f;
        // app名
        std::string name = "wow";
        // 日志文件路径
        std::string log_path = "";
        // 默认图标路径
        std::string icon_path = "assets/app.png";
        // 默认字体文件路径
#ifdef WIN32
        std::string font_path = "C:\\Windows\\Fonts\\Dengb.ttf";
#else
        std::string font_path = "/usr/share/fonts/truetype/arphic/ukai.ttc";
#endif
    };

    struct AppCallback {
        // 初始化数据加载
        std::function<bool()> Setup = nullptr;
        // Frame渲染
        std::function<void()> Draw = nullptr;
        // 数据清理
        std::function<bool()> Teardown = nullptr;
        // 主题配置
        std::function<void()> ConfigTheme = nullptr;
    };

    extern WOW_API AppInfo wow_info;
    extern WOW_API AppCallback wow_callback;
}

namespace WowDialog {
    enum TaskState {
        READY,
        START,
        RUNNING,
        STOP,
    };
    //----------------------------
    // 后台加载
    //----------------------------
    class BackendLoading {
    private:
        TaskState state;
    public:
        BackendLoading() {
            state = READY;
        }
        void Display();
        bool IsRunning() {
            return state == RUNNING;
        }
        void Start() {
            state = RUNNING;
        }
        void Stop() {
            state = READY;
        }
    };
    //----------------------------
    // 全局加载
    //----------------------------
    class GlobalLoading {
    private:
        TaskState state;
    public:
        GlobalLoading() {
            state = READY;
        }
        void Display();
        bool IsRunning() {
            return state == RUNNING;
        }
        void Start() {
            state = START;
        }
        void Stop() {
            state = STOP;
        }
    };
    //----------------------------
    // 消息通知窗口
    //----------------------------
    class MessageDialog {
    private:
        // 全局消息状态
        TaskState state;
        // 消息窗口内容
        std::string message;
        // 消息窗口确认回调
        std::function<void()> confirm; // 是否点击确认回调
    public:
        MessageDialog() {
            state = READY;
        }
        void Display();
        void Open(const std::string& msg, std::function<void()> callback = NULL) {
            message = msg;
            confirm = callback;
            state = START;
        }
    };
    //----------------------------
    // 文件选择窗口
    //----------------------------
    struct FileInfo {
        std::string filename;
        bool is_directory;
        bool is_checked;
    };
    class FileDialog {
    private:
        TaskState state;
        std::string file_directory;
        char file_name[256];
        bool is_select_directory;
        bool is_save_file;
        std::list<std::string> exts;
        std::list<FileInfo> fileinfo_list;
        std::list<std::pair<std::string, std::string>> const_directory;
        bool update;
        void UpdateFileInfo(const std::string& dirname);
    public:
        FileDialog();
        void Display();
        void Open();
        std::string GetFileName();
        std::list<std::string> GetFileNames();
        std::string GetSaveName();
        std::string GetDirName();
        void ChangeToSelectFiles();
        void ChangeToSelectDirectory();
        void ChangeToSaveFile();
        void SetFilter(const std::list<std::string>& filters);
    };
    extern WOW_API BackendLoading backend_loading;
    extern WOW_API GlobalLoading global_loading;
    extern WOW_API MessageDialog message_dialog;
    extern WOW_API FileDialog file_dialog;
}

namespace WowTask {
    class TaskResult {
    public:
        // 任务结果
        bool state;
        // 任务结束提示
        std::string message;
        TaskResult(bool result, const std::string& msg = "");
        ~TaskResult();
    };
    // 初始化全局任务线程
    void InitGlobalTaskThread();
    // 初始化后台任务线程
    void InitBackendTaskThread();
    // 关闭全局任务线程
    void ReleaseGlobalTaskThread();
    // 关闭后台任务线程
    void ReleaseBackendTaskThread();
    // 创建全局任务
    void CreateGlobalTask(std::function<TaskResult()> task);
    // 创建后台任务
    void CreateBackendTask(std::function<TaskResult()> task);
}

// 启动APP
int Run();
