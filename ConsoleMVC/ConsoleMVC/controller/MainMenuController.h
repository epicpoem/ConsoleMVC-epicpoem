#pragma once
#include <istream>
#include <array>
#include "IController.h"
#include "../view/IMainMenuView.h"

class MainMenuController : public IController {
public:
    MainMenuController(std::istream& in, IMainMenuView& view,
                       std::array<IController*, 6> subControllers);
    void run() override;

private:
    std::istream& in_;
    IMainMenuView& view_;
    std::array<IController*, 6> subs_;
};
