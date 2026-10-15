#pragma once
#include <string>


class WowConfig {
    public:
        std::string name;
        // ui
        int width;
        int height;
        float font_base;
        // log
        bool log_enabled;
        std::string log_path;
        int log_size;
        int log_num;
        // action
        bool force_close;

        WowConfig();
        void Load();
};
