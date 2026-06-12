#include "MonitoringController.h"
#include <string>

MonitoringController::MonitoringController(std::istream& in, IMonitoringView& view,
                                           OrderRepository& orderRepo, SampleRepository& sampleRepo)
    : in_(in), view_(view), orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

void MonitoringController::run() {
    // TODO: Feature - 실제 주문/재고 데이터 기반으로 계산하여 view에 전달
    view_.showOrderStats(
        orderRepo_.countByStatus(OrderStatus::RESERVED),
        orderRepo_.countByStatus(OrderStatus::PRODUCING),
        orderRepo_.countByStatus(OrderStatus::CONFIRMED),
        orderRepo_.countByStatus(OrderStatus::RELEASE)
    );
    view_.showStockInfo({});

    std::string line;
    std::getline(in_, line);
}
