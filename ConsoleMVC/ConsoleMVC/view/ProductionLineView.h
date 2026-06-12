#pragma once
#include "IProductionLineView.h"

class ProductionLineView : public IProductionLineView {
public:
    void showCurrentProduction(const ProductionItem* item) override;
    void showWaitingQueue(const std::vector<WaitingItem>& queue) override;
    void showReturnPrompt() override;
};
