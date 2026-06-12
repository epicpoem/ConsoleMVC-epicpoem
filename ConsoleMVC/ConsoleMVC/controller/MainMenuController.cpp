#include "MainMenuController.h"
#include <string>

MainMenuController::MainMenuController(std::istream& in, IMainMenuView& view,
                                       std::array<IController*, 6> subControllers)
    : in_(in), view_(view), subs_(subControllers) {}

void MainMenuController::run() {
    while (true) {
        view_.showMenu();
        std::string line;
        std::getline(in_, line);
        if (line.size() == 1 && line[0] >= '1' && line[0] <= '6') {
            subs_[line[0] - '1']->run();
        } else if (line == "0") {
            break;
        } else {
            view_.showInvalidInput();
        }
    }
}
