#include <functional>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "common.h"
// 消除OpenGL弃用警告
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#define IMGUI_ENABLE_FREETYPE
#include "implot.h"
#include "gui.h"
//----------------------------
// 全局状态初始化
//----------------------------
namespace State {
    // 缩放
    float scale = 0;
    // 实时窗口尺寸
    int width = 1280;
    int height = 800;
    // 后台任务运行状态
    TaskState backend_task_state = READY;
    // 全局任务运行状态
    TaskState global_task_state = READY;
    // 全局消息状态
    TaskState global_msg_state = READY;
    // 全局文件选择状态
    TaskState global_file_state = READY;
    // 消息窗口内容
    std::string msg;
    // 消息窗口确认回调
    std::function<void()> confirm = NULL;
    // 是否有任务运行
    bool IsRunning() {
        return backend_task_state != READY || global_task_state != READY;
    }
}
//----------------------------
// 窗口异常回调
//----------------------------
static void glfw_error_callback(int error, const char* description) {
    logger->error("GLFW Error {} : {}", error, description);
}
//----------------------------
// 可选-窗口关闭回调
//----------------------------
static void glfw_close_callback(GLFWwindow* window) {
    Close();
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
//----------------------------
// APP入口
//----------------------------
int main(int, char**) {
    InitLogger();
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return 1;
    }
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_MAXIMIZED, 0);
    glfwWindowHint(GLFW_RESIZABLE, 0);
    // 创建上下文
    State::scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    State::width = (int)(State::width * State::scale);
    State::height = (int)(State::height * State::scale);
    GLFWwindow* window = glfwCreateWindow(State::width, State::height, "WOW", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwSetWindowCloseCallback(window, glfw_close_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    // 初始化上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // 支持键盘控制
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
#ifdef WIN32
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Dengb.ttf");
#else
    io.Fonts->AddFontFromFileTTF("/usr/share/fonts/opentype/noto/NotoSansCJK-Bold.ttc");
#endif
    // 缩放
    InitStyle();
    // 初始化后端GLFW与OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        // 启动 dear imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // draw
        Draw();
        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window, &State::width, &State::height);
        glViewport(0, 0, State::width, State::height);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
