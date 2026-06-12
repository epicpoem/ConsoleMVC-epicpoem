#include "ApprovalController.h"
#include <string>
#include <cmath>
#include <algorithm>

ApprovalController::ApprovalController(std::istream& in, IApprovalView& view,
                                       IOrderRepository& orderRepo, ISampleRepository& sampleRepo,
                                       IClock& clock)
    : in_(in), view_(view), orderRepo_(orderRepo), sampleRepo_(sampleRepo), clock_(clock) {}

void ApprovalController::run() {
    auto reserved = orderRepo_.getByStatus(OrderStatus::RESERVED);
    if (reserved.empty()) {
        view_.showNoReservedOrders();
        return;
    }

    while (true) {
        view_.showReservedOrders(reserved);

        std::string line;
        if (!std::getline(in_, line)) return;
        if (line == "0") return;

        int idx = -1;
        try { idx = std::stoi(line) - 1; } catch (...) {}

        if (idx < 0 || idx >= static_cast<int>(reserved.size())) {
            view_.showInvalidInput();
            continue;
        }

        Order selected = reserved[idx];

        view_.showApproveOrRejectPrompt();
        std::string action;
        if (!std::getline(in_, action)) return;

        if (action == "Y" || action == "y") {
            auto sampleOpt = sampleRepo_.findById(selected.sampleId);
            if (!sampleOpt) {
                view_.showInvalidInput();
                continue;
            }

            // 물리적 재고 = 보유 재고 + 각 PRODUCING 주문의 진행분 비례 합산
            double physicalStock = static_cast<double>(sampleOpt->stock);
            for (const auto& prod : orderRepo_.getByStatus(OrderStatus::PRODUCING)) {
                if (prod.sampleId != selected.sampleId) continue;
                if (prod.totalProductionTimeMin <= 0.0) continue;
                double elapsedSec = std::difftime(clock_.now(), prod.productionStartTime);
                double totalTimeSec = prod.totalProductionTimeMin * 60.0;
                double progress = std::min(1.0, elapsedSec / totalTimeSec);
                physicalStock += prod.actualProduction * progress;
            }
            int physicalStockInt = static_cast<int>(physicalStock);

            if (physicalStockInt >= selected.quantity) {
                selected.status = OrderStatus::CONFIRMED;
                orderRepo_.updateOrder(selected);
                view_.showApprovalResult(selected);
            } else {
                int shortage = selected.quantity - physicalStockInt;
                // SPEC: 실생산량 = ceil(부족분 / (수율 * 0.9))  (0.9 = 10% 공정 오차 보정)
                int actualProd = static_cast<int>(
                    std::ceil(static_cast<double>(shortage) / (sampleOpt->yield * 0.9)));
                double totalTime = sampleOpt->avgProductionTime * actualProd;

                view_.showStockShortage(shortage, actualProd, totalTime);
                std::string confirm;
                if (!std::getline(in_, confirm)) return;

                if (confirm == "Y" || confirm == "y") {
                    selected.status = OrderStatus::PRODUCING;
                    selected.actualProduction = actualProd;
                    selected.totalProductionTimeMin = totalTime;
                    selected.productionStartTime = clock_.now();
                    orderRepo_.updateOrder(selected);
                    view_.showApprovalResult(selected);
                }
            }
        } else if (action == "N" || action == "n") {
            selected.status = OrderStatus::REJECTED;
            orderRepo_.updateOrder(selected);
            view_.showRejectionResult(selected);
        } else {
            view_.showInvalidInput();
            continue;
        }

        reserved = orderRepo_.getByStatus(OrderStatus::RESERVED);
        if (reserved.empty()) return;
    }
}
