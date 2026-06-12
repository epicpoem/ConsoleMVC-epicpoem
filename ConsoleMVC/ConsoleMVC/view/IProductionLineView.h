#pragma once
#include <vector>
#include <string>

struct ProductionItem {
    std::string orderNo;
    std::string sampleName;
    int orderedQty{0};
    int stock{0};
    int shortage{0};
    int actualProduction{0};
    double progressRate{0.0};
    double estimatedCompletionMin{0.0};
};

struct WaitingItem {
    int queuePosition{0};
    std::string orderNo;
    std::string sampleName;
    int orderedQty{0};
    int shortage{0};
    int actualProduction{0};
    double estimatedCompletionMin{0.0};
};

class IProductionLineView {
public:
    virtual ~IProductionLineView() = default;
    virtual void showCurrentProduction(const ProductionItem* item) = 0;
    virtual void showWaitingQueue(const std::vector<WaitingItem>& queue) = 0;
    virtual void showReturnPrompt() = 0;
};
