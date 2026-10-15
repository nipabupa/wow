#include "wow_thread.h"


WowThread::WowThread() {
    // TODO app注册
}

bool WowThread::isRunning() {
    return running;
}

void WowThread::stop() {
    running = false;
    if(t != nullptr && t->joinable()) {
        t->join();
    }
}

void WowThread::run() {
    exec();
}

void WowThread::exec() {
}


