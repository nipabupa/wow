#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_extends.h"
#include "wow_app.h"
#include "wow_common.h"
// 消除OpenGL弃用警告
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#define IMGUI_ENABLE_FREETYPE
#ifdef BUILD_IMPLOT
#include "implot.h"
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


WowApp::WowApp() {
    self = this;
    // 配置文件加载
    config.Load();
    // 初始化日志
    if(config.log_enabled) {
        logger = WowUtils::InitFileLogger(config.log_path, config.log_size, config.log_num);
    } else {
        logger = WowUtils::InitConsoleLogger();
    }
    // 加载主题
    theme.Load();
}

void WowApp::glfwErrorCallback(int error, const char* description) {
    self->logger->error("GLFW Error {} : {}", error, description);
}

void WowApp::glfwCloseCallback(GLFWwindow* window) {
    for(auto& task : self->thread_list) {
        if(task.isRunning()) {
            self->logger->warn("App thread {} is running", task.name);
            glfwSetWindowShouldClose(window, GLFW_FALSE);
            if(self->config.force_close) {
                task.stop();
            } else {
                return;
            }
        }
    }
}

void WowApp::exec() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        logger->error("GLFW初始化失败");
        return;
    }
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_MAXIMIZED, 0);
    glfwWindowHint(GLFW_RESIZABLE, 0);
    // 创建上下文
    float scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    config.width = (int)(config.width * scale);
    config.height = (int)(config.height * scale);
    GLFWwindow* window = glfwCreateWindow(config.width, config.height, config.name.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        logger->error("GLFW窗口创建失败");
        return;
    }
    glfwSetWindowCloseCallback(window, glfwCloseCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    GLFWimage icon;
    if(fs::exists(app_info.icon_path)) {
        icon.pixels = stbi_load(app_info.icon_path.c_str(), &icon.width, &icon.height, 0, 4);
        if(!icon.pixels) {
            WowCommon::logger->error("加载APP图标失败");
            return 1;
        }
        glfwSetWindowIcon(window, 1, &icon);
    }
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
        WowDialog::message_dialog.Display();
        WowDialog::file_dialog.Display();
        WowDialog::global_loading.Display();
        WowDialog::backend_loading.Display();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        ImGui::Begin("app", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings);
        ImGui::PopStyleVar();
        app_callback.Draw();
        if (ImGui::GetWindowPos().y != 0) {
            ImGui::SetWindowSize(ImVec2(app_info.width, app_info.height));
            ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
        }
        ImGui::End();
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
    if(icon.pixels != nullptr) {
        free(icon.pixels);
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
