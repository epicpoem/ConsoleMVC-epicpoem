#include "MonitoringView.h"
#include <iostream>
#include <iomanip>

void MonitoringView::showOrderStats(int reserved, int producing, int confirmed, int release) {
    std::cout << "\n[모니터링] 주문 현황\n";
    std::cout << std::string(40, '-') << "\n";
    std::cout << std::left << std::setw(16) << "RESERVED"  << reserved  << " 건\n";
    std::cout << std::left << std::setw(16) << "PRODUCING" << producing << " 건\n";
    std::cout << std::left << std::setw(16) << "CONFIRMED" << confirmed << " 건\n";
    std::cout << std::left << std::setw(16) << "RELEASE"   << release   << " 건\n";
}

void MonitoringView::showStockInfo(const std::vector<StockInfo>& stocks) {
    std::cout << "\n[모니터링] 재고 현황\n";
    std::cout << std::string(56, '-') << "\n";
    if (stocks.empty()) {
        std::cout << "  등록된 시료가 없습니다.\n";
        return;
    }
    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(20) << "이름"
              << std::setw(8)  << "재고"
              << std::setw(8)  << "주문량"
              << "상태\n";
    std::cout << std::string(56, '-') << "\n";
    for (const auto& info : stocks) {
        const char* status = "";
        if (info.stockStatus == StockStatus::DEPLETED)      status = "고갈";
        else if (info.stockStatus == StockStatus::INSUFFICIENT) status = "부족";
        else                                                 status = "여유";

        std::cout << std::setw(10) << info.sample.id
                  << std::setw(20) << info.sample.name
                  << std::setw(8)  << info.sample.stock
                  << std::setw(8)  << info.confirmedAndProducingQty
                  << status << "\n";
    }
}
