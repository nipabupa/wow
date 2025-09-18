#include <functional>


namespace TaskManager {
    void Add(std::function<void()> task);
    bool IsRunning();
}
