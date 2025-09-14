#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "utils.h"
#include "ui.h"
// 消除OpenGL弃用警告
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#define IMGUI_ENABLE_FREETYPE


std::shared_ptr<spdlog::logger> logger;


static void glfw_error_callback(int error, const char* description)
{
    spdlog::error("GLFW Error {} : {}", error, description);
}

int main(int, char**)
{
    spdlog::cfg::load_env_levels("WOW_LOG_LEVEL");
    // 5MB, Max 5
    logger = spdlog::rotating_logger_mt("wow_logger", "wow.txt", 1048576 * 5, 5);
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return 1;
    }
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // 创建上下文
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    // 初始化上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // 支持键盘控制
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // 主题
    ImGui::StyleColorsDark();
    // 缩放
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;
    // 初始化后端GLFW与OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    // 字体
    style.FontSizeBase = 40.0f;
#ifdef _WIN32
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\Deng.ttf");
#else
    io.Fonts->AddFontFromFileTTF("/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc");
#endif
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
        draw();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
