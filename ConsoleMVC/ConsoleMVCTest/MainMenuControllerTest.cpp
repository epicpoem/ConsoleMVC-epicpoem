#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <array>
#include "../ConsoleMVC/controller/MainMenuController.h"
#include "../ConsoleMVC/controller/IController.h"
#include "../ConsoleMVC/view/IMainMenuView.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;

class MockMainMenuView : public IMainMenuView {
public:
    MOCK_METHOD(void, showMenu, (), (override));
    MOCK_METHOD(void, showInvalidInput, (), (override));
};

class MockController : public IController {
public:
    MOCK_METHOD(void, run, (), (override));
};

class MainMenuControllerTest : public ::testing::Test {
protected:
    MockController mockSample, mockOrder, mockApproval,
                   mockMonitoring, mockProdLine, mockRelease;
    std::array<IController*, 6> subs;

    void SetUp() override {
        subs = { &mockSample, &mockOrder, &mockApproval,
                 &mockMonitoring, &mockProdLine, &mockRelease };
    }
};

TEST_F(MainMenuControllerTest, InputZeroExitsLoop) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(view, showMenu()).Times(1);
    ctrl.run();
}

TEST_F(MainMenuControllerTest, InvalidInputShowsError) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("9\n0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(view, showInvalidInput()).Times(1);
    ctrl.run();
}

TEST_F(MainMenuControllerTest, InputOneInvokesSampleController) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("1\n0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(mockSample, run()).Times(1);
    ctrl.run();
}

TEST_F(MainMenuControllerTest, InputTwoInvokesOrderController) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("2\n0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(mockOrder, run()).Times(1);
    ctrl.run();
}

TEST_F(MainMenuControllerTest, InputThreeInvokesApprovalController) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("3\n0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(mockApproval, run()).Times(1);
    ctrl.run();
}

TEST_F(MainMenuControllerTest, InputFourInvokesMonitoringController) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("4\n0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(mockMonitoring, run()).Times(1);
    ctrl.run();
}

TEST_F(MainMenuControllerTest, InputFiveInvokesProductionLineController) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("5\n0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(mockProdLine, run()).Times(1);
    ctrl.run();
}

TEST_F(MainMenuControllerTest, InputSixInvokesReleaseController) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("6\n0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(mockRelease, run()).Times(1);
    ctrl.run();
}

TEST_F(MainMenuControllerTest, AllMenuOptionsInvokeCorrectControllers) {
    NiceMock<MockMainMenuView> view;
    std::istringstream in("1\n2\n3\n4\n5\n6\n0\n");
    MainMenuController ctrl(in, view, subs);

    EXPECT_CALL(mockSample,    run()).Times(1);
    EXPECT_CALL(mockOrder,     run()).Times(1);
    EXPECT_CALL(mockApproval,  run()).Times(1);
    EXPECT_CALL(mockMonitoring,run()).Times(1);
    EXPECT_CALL(mockProdLine,  run()).Times(1);
    EXPECT_CALL(mockRelease,   run()).Times(1);
    ctrl.run();
}
