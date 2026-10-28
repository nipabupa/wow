#pragma once
#include <string>
#include <atomic>
#include <mutex>
#include <list>

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
