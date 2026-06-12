#include "ReleaseController.h"
#include <string>

ReleaseController::ReleaseController(std::istream& in, IReleaseView& view,
                                     OrderRepository& orderRepo)
    : in_(in), view_(view), orderRepo_(orderRepo) {}

void ReleaseController::run() {
    auto confirmed = orderRepo_.getByStatus(OrderStatus::CONFIRMED);
    if (confirmed.empty()) {
        view_.showNoConfirmedOrders();
        return;
    }

    while (true) {
        view_.showConfirmedOrders(confirmed);
        std::string line;
        std::getline(in_, line);
        if (line == "0") return;

        // TODO: Feature - 출고 처리 로직 구현
        // 1. 선택한 인덱스 검증
        // 2. 주문 상태 RELEASE로 전환
        // 3. 재고 차감
        // 4. showReleaseSuccess() 호출
        view_.showInvalidInput();
    }
}
