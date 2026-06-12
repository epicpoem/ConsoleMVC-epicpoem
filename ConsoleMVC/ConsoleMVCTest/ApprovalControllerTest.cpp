#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../ConsoleMVC/controller/ApprovalController.h"
#include "../ConsoleMVC/view/IApprovalView.h"
#include "../ConsoleMVC/model/OrderRepository.h"
#include "../ConsoleMVC/model/SampleRepository.h"

using ::testing::_;
using ::testing::NiceMock;

class MockApprovalView : public IApprovalView {
public:
    MOCK_METHOD(void, showReservedOrders, (const std::vector<Order>&), (override));
    MOCK_METHOD(void, showNoReservedOrders, (), (override));
    MOCK_METHOD(void, showInvalidInput, (), (override));
    MOCK_METHOD(void, showApproveOrRejectPrompt, (), (override));
    MOCK_METHOD(void, showApprovalResult, (const Order&), (override));
    MOCK_METHOD(void, showRejectionResult, (const Order&), (override));
    MOCK_METHOD(void, showStockShortage, (int, int, double), (override));
};

class ApprovalControllerTest : public ::testing::Test {
protected:
    OrderRepository  orderRepo;
    SampleRepository sampleRepo;
};

TEST_F(ApprovalControllerTest, ShowsNoReservedOrdersWhenEmpty) {
    NiceMock<MockApprovalView> view;
    std::istringstream in("");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showNoReservedOrders()).Times(1);
    ctrl.run();
}

TEST_F(ApprovalControllerTest, ShowsReservedOrderListWhenExists) {
    orderRepo.add({"ORD-20260612-0001", "S-001", "Customer", 10, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showReservedOrders(_)).Times(1);
    ctrl.run();
}

TEST_F(ApprovalControllerTest, InputZeroReturnsToMain) {
    orderRepo.add({"ORD-20260612-0001", "S-001", "Customer", 10, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo);

    ctrl.run();  // should not loop infinitely
}

TEST_F(ApprovalControllerTest, ApproveWithSufficientStock_BecomesConfirmed) {
    sampleRepo.add({"S-001", "Sample", 0.5, 0.9, 100});
    orderRepo.add({"ORD-0001", "S-001", "Customer", 50, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nY\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showApprovalResult(_)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::CONFIRMED), 1);
}

TEST_F(ApprovalControllerTest, ApproveWithInsufficientStock_BecomesProducing) {
    sampleRepo.add({"S-001", "Sample", 0.5, 0.9, 10});
    orderRepo.add({"ORD-0001", "S-001", "Customer", 100, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nY\nY\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showStockShortage(_, _, _)).Times(1);
    EXPECT_CALL(view, showApprovalResult(_)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::PRODUCING), 1);
}

TEST_F(ApprovalControllerTest, RejectOrder_BecomesRejected) {
    orderRepo.add({"ORD-0001", "S-001", "Customer", 50, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nN\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showRejectionResult(_)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::REJECTED), 1);
}
