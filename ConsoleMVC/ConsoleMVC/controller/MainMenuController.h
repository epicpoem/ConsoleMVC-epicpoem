#pragma once
#include <istream>
#include <array>
#include "IController.h"
#include "../view/IMainMenuView.h"
#include "../model/ISampleRepository.h"
#include "../model/IOrderRepository.h"

class MainMenuController : public IController {
public:
    MainMenuController(std::istream& in, IMainMenuView& view,
                       std::array<IController*, 6> subControllers,
                       ISampleRepository& sampleRepo, IOrderRepository& orderRepo);
    void run() override;

private:
    std::istream& in_;
    IMainMenuView& view_;
    std::array<IController*, 6> subs_;
    ISampleRepository& sampleRepo_;
    IOrderRepository& orderRepo_;
};
