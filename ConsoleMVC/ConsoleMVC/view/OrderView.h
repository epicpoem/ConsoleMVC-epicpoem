#pragma once
#include "IOrderView.h"

class OrderView : public IOrderView {
public:
    void showOrderForm() override;
    void showSampleIdPrompt() override;
    void showCustomerNamePrompt() override;
    void showQuantityPrompt() override;
    void showOrderSuccess(const Order& order) override;
    void showInvalidSampleId() override;
    void showInvalidQuantity() override;
};
