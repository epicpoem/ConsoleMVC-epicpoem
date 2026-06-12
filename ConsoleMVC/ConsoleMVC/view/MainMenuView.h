#pragma once
#include "IMainMenuView.h"

class MainMenuView : public IMainMenuView {
public:
    void showMenu() override;
    void showInvalidInput() override;
};
