#pragma once
#include <string>


class WowConfig {
    public:
        std::string name_;
        // ui
        int width_;
        int height_;
        float fontBase_;
        // log
        bool logEnabled_;
        std::string logPath_;
        int logSize_;
        int logNum_;
        // action
        bool forceClose_;
        // icon
        std::string iconPath_ = "assets/app.icon";

        WowConfig();
        void Load();
};
