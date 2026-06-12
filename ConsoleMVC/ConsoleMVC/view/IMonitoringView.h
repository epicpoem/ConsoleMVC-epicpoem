#pragma once
#include <vector>
#include <string>
#include "../model/Sample.h"

enum class StockStatus { SUFFICIENT, INSUFFICIENT, DEPLETED };

struct StockInfo {
    Sample sample;
    StockStatus stockStatus;
    int confirmedAndProducingQty;
};

class IMonitoringView {
public:
    virtual ~IMonitoringView() = default;
    virtual void showOrderStats(int reserved, int producing, int confirmed, int release) = 0;
    virtual void showStockInfo(const std::vector<StockInfo>& stocks) = 0;
};
