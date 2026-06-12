#pragma once
#include "../model/Order.h"

class IOrderView {
public:
    virtual ~IOrderView() = default;
    virtual void showOrderForm() = 0;
    virtual void showOrderSuccess(const Order& order) = 0;
    virtual void showInvalidSampleId() = 0;
    virtual void showInvalidQuantity() = 0;
};
