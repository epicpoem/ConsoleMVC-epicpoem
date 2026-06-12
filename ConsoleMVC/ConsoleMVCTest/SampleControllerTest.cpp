#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../ConsoleMVC/controller/SampleController.h"
#include "../ConsoleMVC/view/ISampleView.h"
#include "../ConsoleMVC/model/SampleRepository.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;

class MockSampleView : public ISampleView {
public:
    MOCK_METHOD(void, showMenu, (), (override));
    MOCK_METHOD(void, showInvalidInput, (), (override));
    MOCK_METHOD(void, showRegisterPrompt, (), (override));
    MOCK_METHOD(void, showRegisterSuccess, (const Sample&), (override));
    MOCK_METHOD(void, showDuplicateId, (), (override));
    MOCK_METHOD(void, showSampleList, (const std::vector<Sample>&), (override));
    MOCK_METHOD(void, showSearchMenu, (), (override));
    MOCK_METHOD(void, showSearchResult, (const std::vector<Sample>&), (override));
    MOCK_METHOD(void, showNoResults, (), (override));
};

class SampleControllerTest : public ::testing::Test {
protected:
    SampleRepository repo;
};

TEST_F(SampleControllerTest, InputZeroReturnsToMain) {
    NiceMock<MockSampleView> view;
    std::istringstream in("0\n");
    SampleController ctrl(in, view, repo);

    EXPECT_CALL(view, showMenu()).Times(1);
    ctrl.run();
}

TEST_F(SampleControllerTest, InvalidInputShowsError) {
    NiceMock<MockSampleView> view;
    std::istringstream in("9\n0\n");
    SampleController ctrl(in, view, repo);

    EXPECT_CALL(view, showInvalidInput()).Times(1);
    ctrl.run();
}

TEST_F(SampleControllerTest, InputOneShowsRegisterPrompt) {
    NiceMock<MockSampleView> view;
    std::istringstream in("1\n0\n");
    SampleController ctrl(in, view, repo);

    EXPECT_CALL(view, showRegisterPrompt()).Times(1);
    ctrl.run();
}

TEST_F(SampleControllerTest, InputTwoShowsSampleList) {
    NiceMock<MockSampleView> view;
    std::istringstream in("2\n0\n");
    SampleController ctrl(in, view, repo);

    EXPECT_CALL(view, showSampleList(_)).Times(1);
    ctrl.run();
}

TEST_F(SampleControllerTest, InputThreeShowsSearchMenu) {
    NiceMock<MockSampleView> view;
    std::istringstream in("3\n0\n");
    SampleController ctrl(in, view, repo);

    EXPECT_CALL(view, showSearchMenu()).Times(1);
    ctrl.run();
}

// TODO: Feature 구현 후 활성화
// TEST_F(SampleControllerTest, RegisterSampleSuccessWithValidInput) {
//     NiceMock<MockSampleView> view;
//     std::istringstream in("1\nS-001\n실리콘 웨이퍼\n0.5\n0.92\n0\n");
//     SampleController ctrl(in, view, repo);
//
//     EXPECT_CALL(view, showRegisterSuccess(_)).Times(1);
//     ctrl.run();
//     EXPECT_TRUE(repo.exists("S-001"));
// }

// TODO: Feature 구현 후 활성화
// TEST_F(SampleControllerTest, RegisterDuplicateIdShowsError) {
//     repo.add({"S-001", "기존 시료", 0.5, 0.9, 0});
//     NiceMock<MockSampleView> view;
//     std::istringstream in("1\nS-001\n중복 시료\n0.5\n0.9\nS-002\n다른시료\n0.5\n0.9\n0\n");
//     SampleController ctrl(in, view, repo);
//
//     EXPECT_CALL(view, showDuplicateId()).Times(1);
//     ctrl.run();
// }
