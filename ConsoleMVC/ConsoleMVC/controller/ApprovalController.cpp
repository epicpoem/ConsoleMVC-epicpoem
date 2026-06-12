#include "ApprovalController.h"
#include <string>

ApprovalController::ApprovalController(std::istream& in, IApprovalView& view,
                                       OrderRepository& orderRepo, SampleRepository& sampleRepo)
    : in_(in), view_(view), orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

void ApprovalController::run() {
    auto reserved = orderRepo_.getByStatus(OrderStatus::RESERVED);
    if (reserved.empty()) {
        view_.showNoReservedOrders();
        return;
    }

    while (true) {
        view_.showReservedOrders(reserved);
        std::string line;
        std::getline(in_, line);
        if (line == "0") return;

        // TODO: Feature - 주문 승인/거절 처리 로직 구현
        // 1. 선택한 인덱스 검증
        // 2. 승인/거절 선택
        // 3. 재고 확인 후 상태 전환 (CONFIRMED / PRODUCING / REJECTED)
        view_.showInvalidInput();
    }
}
