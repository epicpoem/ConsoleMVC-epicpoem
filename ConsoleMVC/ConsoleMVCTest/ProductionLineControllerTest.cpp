#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../ConsoleMVC/controller/ProductionLineController.h"
#include "../ConsoleMVC/view/IProductionLineView.h"
#include "../ConsoleMVC/model/OrderRepository.h"

using ::testing::_;
using ::testing::IsNull;
using ::testing::NiceMock;

class MockProductionLineView : public IProductionLineView {
public:
    MOCK_METHOD(void, showCurrentProduction, (const ProductionItem*), (override));
    MOCK_METHOD(void, showWaitingQueue, (const std::vector<WaitingItem>&), (override));
    MOCK_METHOD(void, showReturnPrompt, (), (override));
};

class ProductionLineControllerTest : public ::testing::Test {
protected:
    OrderRepository orderRepo;
};

TEST_F(ProductionLineControllerTest, ShowsCurrentProductionOnRun) {
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo);

    EXPECT_CALL(view, showCurrentProduction(_)).Times(1);
    ctrl.run();
}

TEST_F(ProductionLineControllerTest, ShowsWaitingQueueOnRun) {
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo);

    EXPECT_CALL(view, showWaitingQueue(_)).Times(1);
    ctrl.run();
}

TEST_F(ProductionLineControllerTest, ShowsNullProductionWhenNoProducingOrder) {
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo);

    EXPECT_CALL(view, showCurrentProduction(IsNull())).Times(1);
    ctrl.run();
}

TEST_F(ProductionLineControllerTest, ShowsProductionItemWhenProducingOrderExists) {
    orderRepo.add({"ORD-0001", "S-001", "Customer", 100, OrderStatus::PRODUCING});
    NiceMock<MockProductionLineView> view;
    std::istringstream in("\n");
    ProductionLineController ctrl(in, view, orderRepo);

    EXPECT_CALL(view, showCurrentProduction(testing::NotNull())).Times(1);
    ctrl.run();
}
