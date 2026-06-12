#include "OrderController.h"
#include <string>

OrderController::OrderController(std::istream& in, IOrderView& view,
                                 SampleRepository& sampleRepo, OrderRepository& orderRepo)
    : in_(in), view_(view), sampleRepo_(sampleRepo), orderRepo_(orderRepo) {}

void OrderController::run() {
    // TODO: Feature - 시료 주문 처리 로직 구현
    // 1. showOrderForm() 으로 입력 유도
    // 2. sampleId, customerName, quantity 입력 처리
    // 3. sampleRepo_ 에서 시료 존재 확인
    // 4. orderRepo_.generateOrderNo() 로 주문번호 생성
    // 5. 주문 등록 및 showOrderSuccess() 호출
    view_.showOrderForm();
}
