#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../ConsoleMVC/controller/ReleaseController.h"
#include "../ConsoleMVC/view/IReleaseView.h"
#include "../ConsoleMVC/model/OrderRepository.h"
#include "../ConsoleMVC/model/SampleRepository.h"

using ::testing::_;
using ::testing::NiceMock;

class MockReleaseView : public IReleaseView {
public:
    MOCK_METHOD(void, showConfirmedOrders, (const std::vector<Order>&), (override));
    MOCK_METHOD(void, showNoConfirmedOrders, (), (override));
    MOCK_METHOD(void, showInvalidInput, (), (override));
    MOCK_METHOD(void, showReleaseSuccess, (const Order&, const std::string&), (override));
};

class ReleaseControllerTest : public ::testing::Test {
protected:
    OrderRepository  orderRepo;
    SampleRepository sampleRepo;
};

TEST_F(ReleaseControllerTest, ShowsNoConfirmedOrdersWhenEmpty) {
    NiceMock<MockReleaseView> view;
    std::istringstream in("");
    ReleaseController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showNoConfirmedOrders()).Times(1);
    ctrl.run();
}

TEST_F(ReleaseControllerTest, ShowsConfirmedOrderListWhenExists) {
    orderRepo.add({"ORD-20260612-0001", "S-001", "Customer", 10, OrderStatus::CONFIRMED});
    NiceMock<MockReleaseView> view;
    std::istringstream in("0\n");
    ReleaseController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showConfirmedOrders(_)).Times(1);
    ctrl.run();
}

TEST_F(ReleaseControllerTest, InputZeroReturnsToMain) {
    orderRepo.add({"ORD-20260612-0001", "S-001", "Customer", 10, OrderStatus::CONFIRMED});
    NiceMock<MockReleaseView> view;
    std::istringstream in("0\n");
    ReleaseController ctrl(in, view, orderRepo, sampleRepo);

    ctrl.run();  // should not loop infinitely
}

TEST_F(ReleaseControllerTest, SelectOrderProcessesRelease) {
    orderRepo.add({"ORD-0001", "S-001", "Customer", 10, OrderStatus::CONFIRMED});
    NiceMock<MockReleaseView> view;
    std::istringstream in("1\n0\n");
    ReleaseController ctrl(in, view, orderRepo, sampleRepo);

    EXPECT_CALL(view, showReleaseSuccess(_, _)).Times(1);
    ctrl.run();
    EXPECT_EQ(orderRepo.countByStatus(OrderStatus::RELEASE), 1);
}
