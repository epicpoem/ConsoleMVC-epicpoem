#include "ApprovalView.h"
#include <iostream>
#include <iomanip>

void ApprovalView::showReservedOrders(const std::vector<Order>& orders) {
    std::cout << "\n[주문 승인/거절] RESERVED 목록\n";
    if (orders.empty()) {
        showNoReservedOrders();
        return;
    }
    std::cout << std::left
              << std::setw(4)  << "No."
              << std::setw(22) << "주문번호"
              << std::setw(16) << "고객명"
              << std::setw(10) << "시료 ID"
              << std::setw(8)  << "수량\n";
    std::cout << std::string(60, '-') << "\n";
    for (int i = 0; i < static_cast<int>(orders.size()); ++i) {
        std::cout << std::setw(4)  << (i + 1)
                  << std::setw(22) << orders[i].orderNo
                  << std::setw(16) << orders[i].customerName
                  << std::setw(10) << orders[i].sampleId
                  << std::setw(8)  << orders[i].quantity << " ea\n";
    }
    std::cout << "[0] 뒤로\n선택: ";
}

void ApprovalView::showNoReservedOrders() {
    std::cout << "  처리 대기 중인 주문이 없습니다.\n";
}

void ApprovalView::showInvalidInput() {
    std::cout << "[오류] 유효하지 않은 입력입니다.\n";
}

void ApprovalView::showApproveOrRejectPrompt() {
    std::cout << "[Y] 승인 / [N] 거절: ";
}

void ApprovalView::showApprovalResult(const Order& order) {
    std::cout << "[승인 완료] " << order.orderNo
              << " → " << (order.status == OrderStatus::CONFIRMED ? "CONFIRMED" : "PRODUCING") << "\n";
}

void ApprovalView::showRejectionResult(const Order& order) {
    std::cout << "[거절 완료] " << order.orderNo << " → REJECTED\n";
}

void ApprovalView::showStockShortage(int shortage, int actualProduction, double productionTimeMin) {
    std::cout << "재고 부족. 부족분 " << shortage << " ea 승인하시겠습니까?"
              << " (실생산량 " << actualProduction << " ea"
              << " / " << static_cast<int>(productionTimeMin) << " min) [Y/N]: ";
}
