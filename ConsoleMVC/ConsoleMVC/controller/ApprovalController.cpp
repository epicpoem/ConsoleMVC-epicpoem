#include "ApprovalController.h"
#include <string>
#include <cmath>

ApprovalController::ApprovalController(std::istream& in, IApprovalView& view,
                                       OrderRepository& orderRepo, SampleRepository& sampleRepo)
    : in_(in), view_(view), orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

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

            int stock = sampleOpt->stock;
            if (stock >= selected.quantity) {
                selected.status = OrderStatus::CONFIRMED;
                orderRepo_.updateOrder(selected);
                view_.showApprovalResult(selected);
            } else {
                int shortage = selected.quantity - stock;
                int actualProd = static_cast<int>(
                    std::ceil(static_cast<double>(shortage) / sampleOpt->yield));
                double totalTime = sampleOpt->avgProductionTime * actualProd;

                view_.showStockShortage(shortage, actualProd, totalTime);
                std::string confirm;
                if (!std::getline(in_, confirm)) return;

                if (confirm == "Y" || confirm == "y") {
                    selected.status = OrderStatus::PRODUCING;
                    selected.actualProduction = actualProd;
                    selected.totalProductionTimeMin = totalTime;
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
