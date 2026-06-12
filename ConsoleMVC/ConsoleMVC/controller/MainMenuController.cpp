#include "MainMenuController.h"
#include "../model/OrderStatus.h"
#include <string>

MainMenuController::MainMenuController(std::istream& in, IMainMenuView& view,
                                       std::array<IController*, 6> subControllers,
                                       ISampleRepository& sampleRepo, IOrderRepository& orderRepo)
    : in_(in), view_(view), subs_(subControllers),
      sampleRepo_(sampleRepo), orderRepo_(orderRepo) {}

void MainMenuController::run() {
    while (true) {
        auto samples = sampleRepo_.getAll();
        int sampleCount = static_cast<int>(samples.size());
        int totalStock = 0;
        for (const auto& s : samples) totalStock += s.stock;
        int totalOrders = static_cast<int>(orderRepo_.getAll().size());
        int producingCount = orderRepo_.countByStatus(OrderStatus::PRODUCING);
        view_.showSummary(sampleCount, totalStock, totalOrders, producingCount);
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
