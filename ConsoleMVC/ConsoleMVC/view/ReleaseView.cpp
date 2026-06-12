#include "ReleaseView.h"
#include <iostream>
#include <iomanip>

void ReleaseView::showConfirmedOrders(const std::vector<Order>& orders) {
    std::cout << "\n[출고 처리] CONFIRMED 목록\n";
    if (orders.empty()) {
        showNoConfirmedOrders();
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

void ReleaseView::showNoConfirmedOrders() {
    std::cout << "  출고 가능한 주문이 없습니다.\n";
}

void ReleaseView::showInvalidInput() {
    std::cout << "[오류] 유효하지 않은 입력입니다.\n";
}

void ReleaseView::showReleaseSuccess(const Order& order, const std::string& dateTime) {
    std::cout << "\n[출고 완료]\n";
    std::cout << "  주문번호  : " << order.orderNo << "\n";
    std::cout << "  출고 수량 : " << order.quantity << " ea\n";
    std::cout << "  처리 일시 : " << dateTime << "\n";
}
