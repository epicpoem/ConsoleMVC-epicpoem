#pragma once

class IMainMenuView {
public:
    virtual ~IMainMenuView() = default;
    virtual void showSummary(int sampleCount, int totalStock, int totalOrders, int producingCount) = 0;
    virtual void showMenu() = 0;
    virtual void showInvalidInput() = 0;
};
