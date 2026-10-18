#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
// #include "imgui_extends.h"
#include "wow_app.h"
#include "wow_common.h"
#include <filesystem>
// 消除OpenGL弃用警告
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#define IMGUI_ENABLE_FREETYPE
#ifdef BUILD_IMPLOT
#include "implot.h"
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// 自身指针
WowApp* WowApp::self = nullptr;

WowApp::WowApp() {
    self = this;
    // 配置文件加载
    config_.Load();
    // 初始化日志
    if(config_.logEnabled_) {
        logger_ = WowUtils::InitFileLogger(config_.logPath_, config_.logSize_, config_.logNum_);
    } else {
        logger_ = WowUtils::InitConsoleLogger();
    }
    // 加载主题
    theme_.Load();
}

void WowApp::glfwErrorCallback(int error, const char* description) {
    self->logger_->error("GLFW Error {} : {}", error, description);
}

void WowApp::glfwCloseCallback(GLFWwindow* window) {
    if(self->onClose()) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        glfwSetWindowShouldClose(window, GLFW_FALSE);
    }
}

void WowApp::build() {
    // 默认实现
}

void WowApp::onSetup() {
    // 默认实现
}

bool WowApp::onClose() {
    // 默认实现
    return true;
}

void WowApp::exec() {
    glfwSetErrorCallback(glfwErrorCallback);
    int code = glfwInit();
    if (!code) {
        logger_->error("GLFW初始化失败: {}", code);
        return;
    }
    const char* glsl_version = "#version 130";   // TODO confirm
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_MAXIMIZED, 0);
    glfwWindowHint(GLFW_RESIZABLE, 0);
    // 创建上下文
    float scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    // 根据系统缩放重新配置分辨率
    config_.width_ = (int)(config_.width_ * scale);
    config_.height_ = (int)(config_.height_ * scale);
    GLFWwindow* window = glfwCreateWindow(config_.width_, config_.height_, config_.name_.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        logger_->error("GLFW窗口创建失败");
        return;
    }
    // glfwSetWindowCloseCallback(window, glfwCloseCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    // icon
    GLFWimage icon;
    if(std::filesystem::exists(config_.iconPath_)) {
        icon.pixels = stbi_load(config_.iconPath_.c_str(), &icon.width, &icon.height, 0, 4);
        if(!icon.pixels) {
            logger_->error("加载APP图标失败");
            return;
        }
        glfwSetWindowIcon(window, 1, &icon);
    }
    // 生命周期函数
    onSetup();
    // 初始化上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
#ifdef BUILD_IMPLOT
    ImPlot::CreateContext();
#endif
    ImGuiIO& io = ImGui::GetIO();

    // 支持键盘控制
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.Fonts->AddFontFromFileTTF(app_info.font_path.c_str());
    // 缩放
    // InitStyle(scale);
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
        // WowDialog::message_dialog.Display();
        // WowDialog::file_dialog.Display();
        // WowDialog::global_loading.Display();
        // WowDialog::backend_loading.Display();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        ImGui::Begin("app", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings);
        ImGui::PopStyleVar();
        // app_callback.Draw();
        if (ImGui::GetWindowPos().y != 0) {
            ImGui::SetWindowSize(ImVec2(config_.width_, config_.height_));
            ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
        }
        // UI回调
        while(!taskQueue_.empty()) {
            auto task = taskQueue_.front();
            taskQueue_.pop();
            task();
        }
        build();
        ImGui::End();
        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window, &config_.width_, &config_.height_);
        glViewport(0, 0, config_.width_, config_.height_);
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
}
