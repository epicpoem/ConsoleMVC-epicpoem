#include "OrderView.h"
#include <iostream>

void OrderView::showOrderForm() {
    std::cout << "\n[시료 주문]\n";
    std::cout << "시료 ID  : ";
}

void OrderView::showCustomerNamePrompt() {
    std::cout << "고객명   : ";
}

void OrderView::showQuantityPrompt() {
    std::cout << "수량(ea) : ";
}

void OrderView::showOrderSuccess(const Order& order) {
    std::cout << "\n[주문 접수 완료]\n";
    std::cout << "  주문번호: " << order.orderNo << "\n";
    std::cout << "  고객명  : " << order.customerName << "\n";
    std::cout << "  시료 ID : " << order.sampleId << "\n";
    std::cout << "  수량    : " << order.quantity << " ea\n";
    std::cout << "  상태    : RESERVED\n";
}

void OrderView::showInvalidSampleId() {
    std::cout << "[오류] 존재하지 않는 시료 ID입니다.\n";
}

void OrderView::showInvalidQuantity() {
    std::cout << "[오류] 수량은 1 이상의 정수여야 합니다.\n";
}
