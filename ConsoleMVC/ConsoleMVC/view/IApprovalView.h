#pragma once
#include <vector>
#include "../model/Order.h"

class IApprovalView {
public:
    virtual ~IApprovalView() = default;
    virtual void showReservedOrders(const std::vector<Order>& orders) = 0;
    virtual void showNoReservedOrders() = 0;
    virtual void showInvalidInput() = 0;
    virtual void showApprovalResult(const Order& order) = 0;
    virtual void showRejectionResult(const Order& order) = 0;
    virtual void showStockShortage(int shortage, int actualProduction, double productionTimeMin) = 0;
};
