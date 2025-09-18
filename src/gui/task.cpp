#include "task.h"
#include <functional>
#include <thread>


void TaskManager::Add(std::function<void()> task) {
    std::thread t(task);
}

bool TaskManager::IsRunning() {

}
