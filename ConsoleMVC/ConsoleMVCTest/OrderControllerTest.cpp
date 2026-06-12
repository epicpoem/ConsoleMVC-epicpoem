#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../ConsoleMVC/controller/OrderController.h"
#include "../ConsoleMVC/view/IOrderView.h"
#include "../ConsoleMVC/model/SampleRepository.h"
#include "../ConsoleMVC/model/OrderRepository.h"

using ::testing::_;
using ::testing::NiceMock;

class MockOrderView : public IOrderView {
public:
    MOCK_METHOD(void, showOrderForm, (), (override));
    MOCK_METHOD(void, showOrderSuccess, (const Order&), (override));
    MOCK_METHOD(void, showInvalidSampleId, (), (override));
    MOCK_METHOD(void, showInvalidQuantity, (), (override));
};

class OrderControllerTest : public ::testing::Test {
protected:
    SampleRepository sampleRepo;
    OrderRepository  orderRepo;
};

TEST_F(OrderControllerTest, ShowsOrderFormOnRun) {
    NiceMock<MockOrderView> view;
    std::istringstream in("\n");
    OrderController ctrl(in, view, sampleRepo, orderRepo);

    EXPECT_CALL(view, showOrderForm()).Times(1);
    ctrl.run();
}

// TODO: Feature 구현 후 활성화
// TEST_F(OrderControllerTest, ValidInputCreatesOrderWithReservedStatus) {
//     sampleRepo.add({"S-001", "테스트 시료", 0.5, 0.9, 100});
//     NiceMock<MockOrderView> view;
//     std::istringstream in("S-001\n삼성전자\n10\n");
//     OrderController ctrl(in, view, sampleRepo, orderRepo);
//
//     EXPECT_CALL(view, showOrderSuccess(_)).Times(1);
//     ctrl.run();
//     EXPECT_EQ(orderRepo.countByStatus(OrderStatus::RESERVED), 1);
// }

// TODO: Feature 구현 후 활성화
// TEST_F(OrderControllerTest, InvalidSampleIdShowsError) {
//     NiceMock<MockOrderView> view;
//     std::istringstream in("X-999\nS-001\n삼성전자\n10\n");
//     OrderController ctrl(in, view, sampleRepo, orderRepo);
//
//     EXPECT_CALL(view, showInvalidSampleId()).Times(1);
//     ctrl.run();
// }

// TODO: Feature 구현 후 활성화
// TEST_F(OrderControllerTest, ZeroQuantityShowsError) {
//     sampleRepo.add({"S-001", "테스트 시료", 0.5, 0.9, 100});
//     NiceMock<MockOrderView> view;
//     std::istringstream in("S-001\n삼성전자\n0\n10\n");
//     OrderController ctrl(in, view, sampleRepo, orderRepo);
//
//     EXPECT_CALL(view, showInvalidQuantity()).Times(1);
//     ctrl.run();
// }
