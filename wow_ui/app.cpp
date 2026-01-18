#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_extends.h"
#include "wow_ui.h"
#include "wow_common.h"
// 消除OpenGL弃用警告
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#define IMGUI_ENABLE_FREETYPE
#ifdef BUILD_IMPLOT
#include "implot.h"
#endif

//----------------------------
// 主题初始化
//----------------------------
void InitStyle(float scale) {
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiExtendStyle& style_ = ImGui::GetExtendStyle();
    style.FontScaleDpi = scale;
    style.FontSizeBase = WowConfig::wow_info.font_base;
    // color
    auto colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.125f, 0.125f, 0.125f, 1.0f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.140f, 0.140f, 0.140f, 1.0f);
    colors[ImGuiCol_Border] = colors[ImGuiCol_Border];
    colors[ImGuiCol_Text] = ImVec4(0.140f, 0.140f, 0.140f, 1.0f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.463f, 0.463f, 0.463f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.192f, 0.192f, 0.208f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.231f, 0.231f, 0.243f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.271f, 0.271f, 0.282f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.192f, 0.192f, 0.208f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.231f, 0.231f, 0.243f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.271f, 0.271f, 0.282f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.329f, 0.663f, 1.0f, 0.588f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.105f, 0.105f, 0.105f, 0.8f);
    colors[ImGuiCol_PopupBg] = colors[ImGuiCol_ChildBg];
    colors[ImGuiCol_ScrollbarBg] = colors[ImGuiCol_WindowBg];
    if(WowConfig::wow_callback.ConfigTheme != nullptr) {
        WowConfig::wow_callback.ConfigTheme();
    }
    // size
    style.WindowPadding = ImVec2(style.FontSizeBase, style.FontSizeBase);
    style.WindowBorderSize = 1.0f;
    style.WindowRounding = style.FontSizeBase / 2;
    style.ScrollbarSize = style.FontSizeBase / 2;
    style.ScrollbarRounding = style.FontSizeBase / 4;
    style.ChildRounding = style.FontSizeBase / 2;
    style.PopupRounding = style.FontSizeBase / 2;
    style.GrabRounding = style.FontSizeBase / 4;
    style.ItemSpacing = ImVec2(style.FontSizeBase, style.FontSizeBase);
    style.ItemInnerSpacing = ImVec2(style.FontSizeBase / 2, 0);
    style.FramePadding = ImVec2(style.FontSizeBase / 2, style.FontSizeBase / 2);
    style.FrameRounding = style.FontSizeBase / 4;
    style.ChildBorderSize = 2.0f;
    style.ChildRounding = style.FontSizeBase / 4;
    style.PopupRounding = style.FontSizeBase / 4;
    style.CellPadding = ImVec2(style.FontSizeBase / 2, style.FontSizeBase / 4);
    style.ScaleAllSizes(scale);
}
//----------------------------
// 窗口异常回调
//----------------------------
static void glfw_error_callback(int error, const char* description) {
    WowCommon::logger->error("GLFW Error {} : {}", error, description);
}
//----------------------------
// 窗口关闭回调
//----------------------------
static void glfw_close_callback(GLFWwindow* window) {
    if(WowConfig::wow_callback.Teardown != nullptr && WowConfig::wow_callback.Teardown()) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        glfwSetWindowShouldClose(window, GLFW_FALSE);
    }
}
//----------------------------
// APP入口
//----------------------------
int Run() {
    auto& app_info = WowConfig::wow_info;
    auto& app_callback = WowConfig::wow_callback;
    if(app_info.log_path.size() != 0) {
        WowCommon::InitFileLogger(app_info.log_path);
    } else {
        WowCommon::InitConsoleLogger();
    }
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
    float scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    app_info.width = (int)(app_info.width * scale);
    app_info.height = (int)(app_info.height * scale);
    GLFWwindow* window = glfwCreateWindow(app_info.width, app_info.height, app_info.name.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwSetWindowCloseCallback(window, glfw_close_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    // 初始化上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
#ifdef BUILD_IMPLOT
    ImPlot::CreateContext();
#endif
    ImGuiIO& io = ImGui::GetIO();
    // 支持键盘控制
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.Fonts->AddFontFromFileTTF(app_info.font_path.c_str());
    // 缩放
    InitStyle(scale);
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
        app_callback.Draw();
        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window, &app_info.width, &app_info.height);
        glViewport(0, 0, app_info.width, app_info.height);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
#ifdef BUILD_IMPLOT
    ImPlot::DestroyContext();
#endif
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
