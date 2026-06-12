#include "ProductionLineController.h"
#include <string>
#include <algorithm>
#include <cmath>

ProductionLineController::ProductionLineController(std::istream& in, IProductionLineView& view,
                                                   OrderRepository& orderRepo,
                                                   SampleRepository& sampleRepo,
                                                   IClock& clock)
    : in_(in), view_(view), orderRepo_(orderRepo), sampleRepo_(sampleRepo), clock_(clock) {}

void ProductionLineController::run() {
    // PRODUCING → CONFIRMED 자동 전환 (생산 완료 여부 확인)
    for (const auto& order : orderRepo_.getByStatus(OrderStatus::PRODUCING)) {
        if (order.totalProductionTimeMin <= 0.0) continue;
        double elapsedSec = std::difftime(clock_.now(), order.productionStartTime);
        if (elapsedSec >= order.totalProductionTimeMin * 60.0) {
            Order completed = order;
            completed.status = OrderStatus::CONFIRMED;
            orderRepo_.updateOrder(completed);
            sampleRepo_.increaseStock(order.sampleId, order.actualProduction);
        }
    }

    auto producing = orderRepo_.getByStatus(OrderStatus::PRODUCING);

    ProductionItem* currentPtr = nullptr;
    ProductionItem current;
    std::vector<WaitingItem> waitingQueue;

    if (!producing.empty()) {
        const auto& first = producing[0];

        auto sampleOpt = sampleRepo_.findById(first.sampleId);
        std::string sampleName = sampleOpt ? sampleOpt->name : first.sampleId;
        int stock = sampleOpt ? sampleOpt->stock : 0;

        double progressRate = 0.0;
        if (first.totalProductionTimeMin > 0.0) {
            double elapsedSec = std::difftime(clock_.now(), first.productionStartTime);
            double totalTimeSec = first.totalProductionTimeMin * 60.0;
            progressRate = std::min(1.0, elapsedSec / totalTimeSec);
        }

        current.orderNo                = first.orderNo;
        current.sampleName             = sampleName;
        current.orderedQty             = first.quantity;
        current.stock                  = stock;
        current.shortage               = std::max(0, first.quantity - stock);
        current.actualProduction       = first.actualProduction;
        current.progressRate           = progressRate;
        current.estimatedCompletionMin = first.totalProductionTimeMin * (1.0 - progressRate);
        currentPtr = &current;

        for (int i = 1; i < static_cast<int>(producing.size()); ++i) {
            const auto& w = producing[i];
            auto wSample = sampleRepo_.findById(w.sampleId);
            std::string wName = wSample ? wSample->name : w.sampleId;
            int wStock = wSample ? wSample->stock : 0;

            WaitingItem item;
            item.queuePosition       = i;
            item.orderNo             = w.orderNo;
            item.sampleName          = wName;
            item.orderedQty          = w.quantity;
            item.shortage            = std::max(0, w.quantity - wStock);
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
