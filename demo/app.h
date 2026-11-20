#pragma once
#include "wow_app.h"


class Application : public WowApp {
public:
    Application();
    ~Application();
protected:
    void build() override;
    void onSetup() override;
    bool onClose() override;
};
