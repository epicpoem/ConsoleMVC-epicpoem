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
    MOCK_METHOD(void, showSampleIdPrompt, (), (override));
    MOCK_METHOD(void, showCustomerNamePrompt, (), (override));
    MOCK_METHOD(void, showQuantityPrompt, (), (override));
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

TEST_F(OrderControllerTest, ValidInputCreatesOrderWithReservedStatus) {
    sampleRepo.add({"S-001", "Test Sample", 0.5, 0.9, 100});
    NiceMock<MockOrderView> view;
    std::istringstream in("S-001\nCustomer A\n10\n");
    OrderController ctrl(in, view, sampleRepo, orderRepo);

    EXPECT_CALL(view, showOrderSuccess(_)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::RESERVED), 1);
}

TEST_F(OrderControllerTest, InvalidSampleIdShowsError) {
    NiceMock<MockOrderView> view;
    std::istringstream in("X-999\n");
    OrderController ctrl(in, view, sampleRepo, orderRepo);

    EXPECT_CALL(view, showInvalidSampleId()).Times(1);
    ctrl.run();
}

TEST_F(OrderControllerTest, ZeroQuantityShowsError) {
    sampleRepo.add({"S-001", "Test Sample", 0.5, 0.9, 100});
    NiceMock<MockOrderView> view;
    std::istringstream in("S-001\nCustomer A\n0\n");
    OrderController ctrl(in, view, sampleRepo, orderRepo);

    EXPECT_CALL(view, showInvalidQuantity()).Times(1);
    ctrl.run();
}
