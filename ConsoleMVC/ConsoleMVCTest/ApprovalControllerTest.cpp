#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../ConsoleMVC/controller/ApprovalController.h"
#include "../ConsoleMVC/view/IApprovalView.h"
#include "../ConsoleMVC/model/OrderRepository.h"
#include "../ConsoleMVC/model/SampleRepository.h"
#include "../ConsoleMVC/model/IClock.h"

using ::testing::_;
using ::testing::NiceMock;

class FakeClock : public IClock {
public:
    explicit FakeClock(std::time_t t = 0) : time_(t) {}
    std::time_t now() const override { return time_; }
    void setTime(std::time_t t) { time_ = t; }
private:
    std::time_t time_;
};

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
    FakeClock        clock{0};
};

TEST_F(ApprovalControllerTest, ShowsNoReservedOrdersWhenEmpty) {
    NiceMock<MockApprovalView> view;
    std::istringstream in("");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showNoReservedOrders()).Times(1);
    ctrl.run();
}

TEST_F(ApprovalControllerTest, ShowsReservedOrderListWhenExists) {
    orderRepo.add({"ORD-20260612-0001", "S-001", "Customer", 10, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showReservedOrders(_)).Times(1);
    ctrl.run();
}

TEST_F(ApprovalControllerTest, InputZeroReturnsToMain) {
    orderRepo.add({"ORD-20260612-0001", "S-001", "Customer", 10, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, clock);

    ctrl.run();  // should not loop infinitely
}

TEST_F(ApprovalControllerTest, ApproveWithSufficientStock_BecomesConfirmed) {
    sampleRepo.add({"S-001", "Sample", 0.5, 0.9, 100});
    orderRepo.add({"ORD-0001", "S-001", "Customer", 50, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nY\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showApprovalResult(_)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::CONFIRMED), 1);
}

TEST_F(ApprovalControllerTest, ApproveWithInsufficientStock_BecomesProducing) {
    sampleRepo.add({"S-001", "Sample", 0.5, 0.9, 10});
    orderRepo.add({"ORD-0001", "S-001", "Customer", 100, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nY\nY\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showStockShortage(_, _, _)).Times(1);
    EXPECT_CALL(view, showApprovalResult(_)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::PRODUCING), 1);
}

TEST_F(ApprovalControllerTest, RejectOrder_BecomesRejected) {
    orderRepo.add({"ORD-0001", "S-001", "Customer", 50, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nN\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showRejectionResult(_)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::REJECTED), 1);
}

TEST_F(ApprovalControllerTest, ProductionFormula_UsesYieldWithSafetyFactor) {
    // SPEC: 실생산량 = ceil(부족분 / (수율 * 0.9))
    // stock=30, yield=0.92, avgTime=0.8, order qty=200
    // shortage = 200 - 30 = 170
    // actualProd = ceil(170 / (0.92 * 0.9)) = ceil(170 / 0.828) = ceil(205.31) = 206
    sampleRepo.add({"S-001", "SiC Board", 0.8, 0.92, 30});
    orderRepo.add({"ORD-001", "S-001", "Samsung", 200, OrderStatus::RESERVED});
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nY\nY\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showStockShortage(170, 206, _)).Times(1);
    ctrl.run();
}

TEST_F(ApprovalControllerTest, PhysicalStockIncludesProducingProgress) {
    // stock=0, PRODUCING order 50% 완료 (50ea 생산 중), 새 주문 40ea
    // 물리적 재고 = 0 + 100 * 0.5 = 50 → 50 >= 40 → CONFIRMED
    sampleRepo.add({"S-001", "Sample", 0.5, 0.9, 0});

    Order producing;
    producing.orderNo = "ORD-PREV";
    producing.sampleId = "S-001";
    producing.customerName = "Customer";
    producing.quantity = 60;
    producing.status = OrderStatus::PRODUCING;
    producing.actualProduction = 100;
    producing.totalProductionTimeMin = 200.0;  // 200분 = 12000초
    producing.productionStartTime = 0;         // t=0 시작
    orderRepo.add(producing);

    orderRepo.add({"ORD-NEW", "S-001", "Customer2", 40, OrderStatus::RESERVED});

    // FakeClock: t=6000 (6000초 경과 = 50% 진행)
    FakeClock halfwayClock(6000);
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nY\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, halfwayClock);

    EXPECT_CALL(view, showApprovalResult(_)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::CONFIRMED), 1);
}

TEST_F(ApprovalControllerTest, ProducingOrderSetsProductionStartTime) {
    sampleRepo.add({"S-001", "Sample", 0.5, 0.9, 0});
    orderRepo.add({"ORD-0001", "S-001", "Customer", 10, OrderStatus::RESERVED});
    FakeClock fixedClock(12345);
    NiceMock<MockApprovalView> view;
    std::istringstream in("1\nY\nY\n0\n");
    ApprovalController ctrl(in, view, orderRepo, sampleRepo, fixedClock);

    ctrl.run();

    auto producing = orderRepo.getByStatus(OrderStatus::PRODUCING);
    ASSERT_EQ(producing.size(), 1u);
    EXPECT_EQ(producing[0].productionStartTime, 12345);
}
