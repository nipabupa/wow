#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
// #include "imgui_extends.h"
#include "wow_app.h"
#include "wow_common.h"
#include <cstdlib>
#include <filesystem>
// 消除OpenGL弃用警告
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#define IMGUI_ENABLE_FREETYPE
#ifdef EMABLE_IMPLOT
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

void WowApp::glfwContextInit() {
    glfwSetErrorCallback(glfwErrorCallback);     // 设置异常回调
    int code = glfwInit();
    if (!code) {
        logger_->error("GLFW初始化失败: {}", code);
        exit(1);
    }
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);  // 取消默认标题栏
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // 显示器缩放
    theme_.scale_ = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    // 根据系统缩放重新配置分辨率
    config_.width_ = (int)(config_.width_ * theme_.scale_);
    config_.height_ = (int)(config_.height_ * theme_.scale_);
    window_ = glfwCreateWindow(config_.width_, config_.height_, config_.name_.c_str(), nullptr, nullptr);
    if (window_ == nullptr) {
        logger_->error("GLFW窗口创建失败");
        exit(1);
    }
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable vsync
    glfwSetWindowCloseCallback(window_, glfwCloseCallback);
    // icon
    icon_.pixels = nullptr;
    if(std::filesystem::exists(config_.iconPath_)) {
        icon_.pixels = stbi_load(config_.iconPath_.c_str(), &icon_.width, &icon_.height, 0, 4);
        if(!icon_.pixels) {
            logger_->error("加载APP图标失败");
            exit(1);
        }
        glfwSetWindowIcon(window_, 1, &icon_);
    }
}

void WowApp::glfwContextRelease() {
    if(icon_.pixels != nullptr) {
        free(icon_.pixels);
    }
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void WowApp::imguiContextInit() {
    // 初始化上下
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
#ifdef EMABLE_IMPLOT
    ImPlot::CreateContext();
#endif
    theme_.buildFonts(config_);
    theme_.buildStyle();
    // 初始化后端GLFW与OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init(nullptr);
}

void WowApp::imguiContextRelease() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
#ifdef EMABLE_IMPLOT
    ImPlot::DestroyContext();
#endif
    ImGui::DestroyContext();
}

void WowApp::render() {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Main loop
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window_, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        // 启动 dear imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // UI回调
        while(!taskQueue_.empty()) {
            auto task = taskQueue_.front();
            taskQueue_.pop();
            task();
        }

        // draw
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
        if(ImGui::Begin("app", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings)) {
            ImGui::PopStyleVar();
            build();
        }
        ImGui::End();

        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window_, &config_.width_, &config_.height_);
        glViewport(0, 0, config_.width_, config_.height_);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
    }
}

void WowApp::exec() {
    glfwContextInit();
    imguiContextInit();
    onSetup();            // 生命周期函数
    render();
    imguiContextRelease();
    glfwContextRelease();
}
