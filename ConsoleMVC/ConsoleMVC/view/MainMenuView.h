#pragma once
#include "IMainMenuView.h"

class MainMenuView : public IMainMenuView {
public:
    void showSummary(int sampleCount, int totalStock, int totalOrders, int producingCount) override;
    void showMenu() override;
    void showInvalidInput() override;
};
