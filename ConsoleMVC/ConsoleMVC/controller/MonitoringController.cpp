#include "MonitoringController.h"
#include "../view/IMonitoringView.h"
#include <string>

MonitoringController::MonitoringController(std::istream& in, IMonitoringView& view,
                                           OrderRepository& orderRepo, SampleRepository& sampleRepo)
    : in_(in), view_(view), orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

void MonitoringController::run() {
    view_.showOrderStats(
        orderRepo_.countByStatus(OrderStatus::RESERVED),
        orderRepo_.countByStatus(OrderStatus::PRODUCING),
        orderRepo_.countByStatus(OrderStatus::CONFIRMED),
        orderRepo_.countByStatus(OrderStatus::RELEASE)
    );

    auto samples = sampleRepo_.getAll();
    std::vector<StockInfo> stockInfos;

    for (const auto& sample : samples) {
        int totalOrdered = 0;
        for (const auto& o : orderRepo_.getByStatus(OrderStatus::CONFIRMED))
            if (o.sampleId == sample.id) totalOrdered += o.quantity;
        for (const auto& o : orderRepo_.getByStatus(OrderStatus::PRODUCING))
            if (o.sampleId == sample.id) totalOrdered += o.quantity;

        StockStatus status;
        if (sample.stock == 0)
            status = StockStatus::DEPLETED;
        else if (sample.stock < totalOrdered)
            status = StockStatus::INSUFFICIENT;
        else
            status = StockStatus::SUFFICIENT;

        stockInfos.push_back({sample, status, totalOrdered});
    }

    view_.showStockInfo(stockInfos);

    std::string line;
    std::getline(in_, line);
}
