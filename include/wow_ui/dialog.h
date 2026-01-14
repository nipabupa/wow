#pragma once
#include <string>
#include <functional>
#include <list>


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
    extern BackendLoading backend_loading;
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
    extern GlobalLoading global_loading;
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
    extern MessageDialog message_dialog;
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
    extern FileDialog file_dialog;
}
