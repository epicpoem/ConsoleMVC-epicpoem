#pragma once
#include "IMonitoringView.h"

class MonitoringView : public IMonitoringView {
public:
    void showOrderStats(int reserved, int producing, int confirmed, int release) override;
    void showStockInfo(const std::vector<StockInfo>& stocks) override;
};
