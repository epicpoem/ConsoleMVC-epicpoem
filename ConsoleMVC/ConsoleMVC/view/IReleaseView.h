#pragma once
#include <vector>
#include <string>
#include "../model/Order.h"

class IReleaseView {
public:
    virtual ~IReleaseView() = default;
    virtual void showConfirmedOrders(const std::vector<Order>& orders) = 0;
    virtual void showNoConfirmedOrders() = 0;
    virtual void showInvalidInput() = 0;
    virtual void showReleaseSuccess(const Order& order, const std::string& dateTime) = 0;
};
