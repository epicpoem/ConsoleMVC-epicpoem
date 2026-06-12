#pragma once
#include "IReleaseView.h"

class ReleaseView : public IReleaseView {
public:
    void showConfirmedOrders(const std::vector<Order>& orders) override;
    void showNoConfirmedOrders() override;
    void showInvalidInput() override;
    void showReleaseSuccess(const Order& order, const std::string& dateTime) override;
};
