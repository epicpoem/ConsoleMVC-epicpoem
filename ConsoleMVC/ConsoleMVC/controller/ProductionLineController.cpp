#include "ProductionLineController.h"
#include <string>

ProductionLineController::ProductionLineController(std::istream& in, IProductionLineView& view,
                                                   OrderRepository& orderRepo)
    : in_(in), view_(view), orderRepo_(orderRepo) {}

void ProductionLineController::run() {
    // TODO: Feature - 실제 생산 진행 상태 계산 후 view에 전달
    view_.showCurrentProduction(nullptr);
    view_.showWaitingQueue({});
    view_.showReturnPrompt();

    std::string line;
    std::getline(in_, line);
}
