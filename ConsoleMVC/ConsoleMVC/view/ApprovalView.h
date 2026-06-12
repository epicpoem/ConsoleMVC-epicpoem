#pragma once
#include "IApprovalView.h"

class ApprovalView : public IApprovalView {
public:
    void showReservedOrders(const std::vector<Order>& orders) override;
    void showNoReservedOrders() override;
    void showInvalidInput() override;
    void showApproveOrRejectPrompt() override;
    void showApprovalResult(const Order& order) override;
    void showRejectionResult(const Order& order) override;
    void showStockShortage(int shortage, int actualProduction, double productionTimeMin) override;
};
