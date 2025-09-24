#include <functional>
#include <string>
#include "imgui.h"
//----------------------------
// 风格常量
//----------------------------
namespace Style {
    const float FontBase = 16.0f;
    const ImVec4 BackgroundColor = ImVec4(0.125f, 0.125f, 0.125f, 1.0f);
    const ImVec4 CardColor = ImVec4(0.140f, 0.140f, 0.140f, 1.0f);
    const ImVec4 PrimaryColor = ImVec4(0.329f, 0.663f, 1.0f, 1.0f);
    const ImVec4 SecondColor = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
    const ImVec4 DangerColor = ImVec4(0.988f, 0.447f, 0.306f, 1.0f);
    const ImVec4 LoadingColor = ImVec4(0.353f, 0.353f, 0.353f, 1.0f);
    const ImVec4 TextColor = ImVec4(0.808f, 0.808f, 0.808f, 1.0f);
    const ImVec2 AutoSize = ImVec2(0, 0);
    const ImU32 RedColor = IM_COL32(255, 0, 0, 255);
    const ImU32 GreenColor = IM_COL32(0, 255, 0, 255);
}
//----------------------------
// 生命周期Hook
//----------------------------
void InitStyle();
void Draw();
void Close();
//----------------------------
// 全局状态
//----------------------------
namespace App {
    enum TaskState {
        READY,
        START,
        RUNNING,
        STOP,
    };
    // 缩放比例
    extern float scale;
    // 实时窗口尺寸
    extern int width;
    extern int height;
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
        void Open(std::string msg, std::function<void()> callback = NULL) {
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
        char filename[256];
        bool is_directory;
        bool is_checked;
    };
    class FileDialog {
    private:
        TaskState state;
        char file_directory[256];
        char file_name[256];
        bool is_directory;
        bool is_save_file;
        std::vector<std::string> exts;
        std::vector<FileInfo> fileinfo_list;
        std::vector<std::pair<std::string, std::string>> const_directory;
        void UpdateFileInfo(const char* dirname);
    public:
        FileDialog();
        void Display();
        void Open() {
            state = START;
        }
        std::string GetFileName();
        void ChangeToSelectDirectory() {
            is_directory = true;
        }
        void ChangeToSaveFile() {
            is_save_file = true;
        }
        void SetFilter(std::vector<std::string> filters) {
            exts = filters;
        }
    };
    extern FileDialog file_dialog;
    //----------------------------
    // 任务管理
    //----------------------------
    // 创建后台任务
    void CreateBackendTask(const char* title, std::function<void()> task);
    // 创建全局任务
    void CreateGlobalTask(const char* title, std::function<void()> task);
}
//----------------------------
// 新增ImGui组件
//----------------------------
namespace ImGui {
    void Title(const char* label, const ImVec4& color = Style::TextColor);
    void Section(const char* label, const ImVec4& color = Style::TextColor);
    bool PrimaryButton(const char* label, const ImVec2& size = Style::AutoSize);
    bool DangerButton(const char* label, const ImVec2& size = Style::AutoSize);
    void Spinner(const char* label, float radius, int thickness, const ImVec4& color);
    void BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
    void ToggleButton(const char* str_id, bool* v, const char* other_label);
    void CustomCombo(const char* label, const char* items[], short size, short& index, void (*callback)() = NULL, int flags = ImGuiComboFlags_None);
}
