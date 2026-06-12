#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../ConsoleMVC/controller/ProductionLineController.h"
#include "../ConsoleMVC/view/IProductionLineView.h"
#include "../ConsoleMVC/model/OrderRepository.h"
#include "../ConsoleMVC/model/SampleRepository.h"
#include "../ConsoleMVC/model/IClock.h"

using ::testing::_;
using ::testing::IsNull;
using ::testing::NiceMock;

class FakeClock : public IClock {
public:
    explicit FakeClock(std::time_t t = 0) : time_(t) {}
    std::time_t now() const override { return time_; }
private:
    std::time_t time_;
};

class MockProductionLineView : public IProductionLineView {
public:
    MOCK_METHOD(void, showCurrentProduction, (const ProductionItem*), (override));
    MOCK_METHOD(void, showWaitingQueue, (const std::vector<WaitingItem>&), (override));
    MOCK_METHOD(void, showReturnPrompt, (), (override));
};

class ProductionLineControllerTest : public ::testing::Test {
protected:
    OrderRepository  orderRepo;
    SampleRepository sampleRepo;
    FakeClock        clock{0};
};

TEST_F(ProductionLineControllerTest, ShowsCurrentProductionOnRun) {
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showCurrentProduction(_)).Times(1);
    ctrl.run();
}

TEST_F(ProductionLineControllerTest, ShowsWaitingQueueOnRun) {
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showWaitingQueue(_)).Times(1);
    ctrl.run();
}

TEST_F(ProductionLineControllerTest, ShowsNullProductionWhenNoProducingOrder) {
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showCurrentProduction(IsNull())).Times(1);
    ctrl.run();
}

TEST_F(ProductionLineControllerTest, ShowsProductionItemWhenProducingOrderExists) {
    // totalProductionTimeMin=0 → auto-transition 조건 skip → PRODUCING 상태 유지
    orderRepo.add({"ORD-0001", "S-001", "Customer", 100, OrderStatus::PRODUCING});
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo, sampleRepo, clock);

    EXPECT_CALL(view, showCurrentProduction(testing::NotNull())).Times(1);
    ctrl.run();
}

TEST_F(ProductionLineControllerTest, AutoTransitionsCompletedProductionToConfirmed) {
    sampleRepo.add({"S-001", "Sample", 0.5, 0.9, 0});

    Order order;
    order.orderNo = "ORD-0001";
    order.sampleId = "S-001";
    order.customerName = "Customer";
    order.quantity = 100;
    order.status = OrderStatus::PRODUCING;
    order.actualProduction = 112;
    order.totalProductionTimeMin = 1.0;  // 1분 = 60초
    order.productionStartTime = 0;       // t=0 시작
    orderRepo.add(order);

    // FakeClock t=120 → 경과 120초 >= 60초 → 생산 완료
    FakeClock completedClock(120);
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo, sampleRepo, completedClock);

    ctrl.run();

    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::CONFIRMED), 1);
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::PRODUCING), 0);
    // increaseStock 호출로 재고 증가 확인
    auto sample = sampleRepo.findById("S-001");
    ASSERT_TRUE(sample.has_value());
    EXPECT_EQ(sample->stock, 112);
}

TEST_F(ProductionLineControllerTest, SampleNameFromRepositoryIsDisplayed) {
    sampleRepo.add({"S-001", "SiC Wafer", 0.5, 0.9, 0});
    // totalProductionTimeMin=0 → auto-transition skip
    orderRepo.add({"ORD-0001", "S-001", "Customer", 100, OrderStatus::PRODUCING});
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo, sampleRepo, clock);

    ProductionItem captured;
    EXPECT_CALL(view, showCurrentProduction(testing::NotNull()))
        .WillOnce([&captured](const ProductionItem* item) {
            captured = *item;
        });
    ctrl.run();

    EXPECT_EQ(captured.sampleName, "SiC Wafer");
}
