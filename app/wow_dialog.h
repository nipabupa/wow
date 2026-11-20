#pragma once
#include <string>
#include <atomic>
#include <mutex>
#include <list>
//****************************************
// 基础空白模态框
//****************************************
class WowDialog {
public:
    WowDialog();
    void show();  // 主循环UI逻辑
    void open();  // 打开窗口, 主线程操作
    void wait();  // 等待关闭, 多线程操作
private:
    std::atomic_bool running_;
    bool isOpen_ = false;
};
//****************************************
// 文件选择框
//****************************************
class WowFileDialog {
public:
    WowFileDialog();

    void show();
    void open(bool is_dir = false, bool multi = false);
    void wait();
    std::string getResult();
    std::list<std::string> getResults();
private:
    std::list<std::string> results_;
    std::atomic_bool running_;
    std::mutex mtx_;
    bool isOpen_ = false;
};
//****************************************
// 消息提示框
//****************************************
// class WowMessageBox {
// public:
//     WowMessageBox();
//
//     void show();
//     void open(std::string& msg);
//
// private:
//     std::string msg_;
//     std::atomic_bool running_;
//     std::mutex mtx_;
// };
//****************************************
// 全局加载框
//****************************************
