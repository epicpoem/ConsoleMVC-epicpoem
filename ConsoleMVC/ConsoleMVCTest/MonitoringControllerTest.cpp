#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../ConsoleMVC/controller/MonitoringController.h"
#include "../ConsoleMVC/view/IMonitoringView.h"
#include "../ConsoleMVC/model/OrderRepository.h"
#include "../ConsoleMVC/model/SampleRepository.h"

using ::testing::_;
using ::testing::NiceMock;

class MockMonitoringView : public IMonitoringView {
public:
    MOCK_METHOD(void, showOrderStats, (int, int, int, int), (override));
    MOCK_METHOD(void, showStockInfo, (const std::vector<StockInfo>&), (override));
};

class MonitoringControllerTest : public ::testing::Test {
protected:
    OrderRepository  orderRepo;
    SampleRepository sampleRepo;
};

TEST_F(MonitoringControllerTest, ShowsOrderStatsOnRun) {
    NiceMock<MockMonitoringView> view;
    std::istringstream in("\n");
    MonitoringController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showOrderStats(_, _, _, _)).Times(1);
    ctrl.run();
}

TEST_F(MonitoringControllerTest, ShowsStockInfoOnRun) {
    NiceMock<MockMonitoringView> view;
    std::istringstream in("\n");
    MonitoringController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showStockInfo(_)).Times(1);
    ctrl.run();
}

TEST_F(MonitoringControllerTest, OrderStatsReflectActualCounts) {
    orderRepo.add({"ORD-0001", "S-001", "A", 10, OrderStatus::RESERVED});
    orderRepo.add({"ORD-0002", "S-001", "B", 10, OrderStatus::PRODUCING});
    orderRepo.add({"ORD-0003", "S-001", "C", 10, OrderStatus::CONFIRMED});
    orderRepo.add({"ORD-0004", "S-001", "D", 10, OrderStatus::RELEASE});

    NiceMock<MockMonitoringView> view;
    std::istringstream in("\n");
    MonitoringController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showOrderStats(1, 1, 1, 1)).Times(1);
    ctrl.run();
}

// TODO: Feature 구현 후 활성화
// TEST_F(MonitoringControllerTest, StockInfoReflectsActualSamples) {
//     sampleRepo.add({"S-001", "시료A", 0.5, 0.9, 100});
//     orderRepo.add({"ORD-0001", "S-001", "고객", 50, OrderStatus::CONFIRMED});
//     NiceMock<MockMonitoringView> view;
//     std::istringstream in("\n");
//     MonitoringController ctrl(in, view, orderRepo, sampleRepo);
//
//     EXPECT_CALL(view, showStockInfo(testing::SizeIs(1))).Times(1);
//     ctrl.run();
// }
