#pragma once
#include "IOrderView.h"

class OrderView : public IOrderView {
public:
    void showOrderForm() override;
    void showOrderSuccess(const Order& order) override;
    void showInvalidSampleId() override;
    void showInvalidQuantity() override;
};
