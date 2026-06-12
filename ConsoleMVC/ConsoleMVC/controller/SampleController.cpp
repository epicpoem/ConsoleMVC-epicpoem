#include "SampleController.h"
#include <string>

SampleController::SampleController(std::istream& in, ISampleView& view, SampleRepository& repo)
    : in_(in), view_(view), repo_(repo) {}

void SampleController::run() {
    while (true) {
        view_.showMenu();
        std::string line;
        std::getline(in_, line);
        if (line == "0") return;
        if (line == "1")      handleRegister();
        else if (line == "2") handleList();
        else if (line == "3") handleSearch();
        else                  view_.showInvalidInput();
    }
}

void SampleController::handleRegister() {
    // TODO: Feature - 시료 등록 로직 구현
    view_.showRegisterPrompt();
}

void SampleController::handleList() {
    // TODO: Feature - 시료 목록 조회
    view_.showSampleList(repo_.getAll());
}

void SampleController::handleSearch() {
    // TODO: Feature - 시료 검색 로직 구현
    view_.showSearchMenu();
}
