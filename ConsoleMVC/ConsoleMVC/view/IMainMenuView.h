#pragma once

class IMainMenuView {
public:
    virtual ~IMainMenuView() = default;
    virtual void showMenu() = 0;
    virtual void showInvalidInput() = 0;
};
