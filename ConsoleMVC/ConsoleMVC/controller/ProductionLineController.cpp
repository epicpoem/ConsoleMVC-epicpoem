#include "ProductionLineController.h"
#include <string>

ProductionLineController::ProductionLineController(std::istream& in, IProductionLineView& view,
                                                   OrderRepository& orderRepo)
    : in_(in), view_(view), orderRepo_(orderRepo) {}

void ProductionLineController::run() {
    auto producing = orderRepo_.getByStatus(OrderStatus::PRODUCING);

    ProductionItem* currentPtr = nullptr;
    ProductionItem current;
    std::vector<WaitingItem> waitingQueue;

    if (!producing.empty()) {
        const auto& first = producing[0];
        current.orderNo            = first.orderNo;
        current.sampleName         = first.sampleId;
        current.orderedQty         = first.quantity;
        current.actualProduction   = first.actualProduction;
        current.progressRate       = 0.0;
        current.estimatedCompletionMin = first.totalProductionTimeMin;
        currentPtr = &current;

        for (int i = 1; i < static_cast<int>(producing.size()); ++i) {
            const auto& w = producing[i];
            WaitingItem item;
            item.queuePosition       = i;
            item.orderNo             = w.orderNo;
            item.sampleName          = w.sampleId;
            item.orderedQty          = w.quantity;
            item.actualProduction    = w.actualProduction;
            item.estimatedCompletionMin = w.totalProductionTimeMin;
            waitingQueue.push_back(item);
        }
    }

    view_.showCurrentProduction(currentPtr);
    view_.showWaitingQueue(waitingQueue);
    view_.showReturnPrompt();

    std::string line;
    std::getline(in_, line);
}
