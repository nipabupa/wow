#pragma once
#include "wow_config.h"


class WowTheme {
    public:
        WowTheme();
        void Load();

        // 字体基准
        float fontBase_ = 25;
        // 显示缩放
        float scale_;

        void buildStyle();
        void buildFonts(WowConfig& config);
};
