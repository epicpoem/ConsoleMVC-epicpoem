#include "SampleView.h"
#include <iostream>
#include <iomanip>

void SampleView::showMenu() {
    std::cout << "\n--- 시료 관리 ---\n";
    std::cout << " [1] 시료 등록\n";
    std::cout << " [2] 시료 조회\n";
    std::cout << " [3] 시료 검색\n";
    std::cout << " [0] 뒤로\n";
    std::cout << "선택: ";
}

void SampleView::showInvalidInput() {
    std::cout << "[오류] 유효하지 않은 입력입니다.\n";
}

void SampleView::showRegisterPrompt() {
    std::cout << "\n[시료 등록]\n";
    std::cout << "시료 ID   : ";
}

void SampleView::showNamePrompt() {
    std::cout << "이름      : ";
}

void SampleView::showTimePrompt() {
    std::cout << "평균생산시간(min/ea): ";
}

void SampleView::showYieldPrompt() {
    std::cout << "수율(0~1) : ";
}

void SampleView::showYieldOutOfRange() {
    std::cout << "[오류] 수율은 0.0 ~ 1.0 사이의 값이어야 합니다.\n";
}

void SampleView::showRegisterSuccess(const Sample& sample) {
    std::cout << "[성공] 시료가 등록되었습니다.\n";
    std::cout << "  ID: " << sample.id
              << " | 이름: " << sample.name
              << " | 평균생산시간: " << sample.avgProductionTime << " min/ea"
              << " | 수율: " << sample.yield << "\n";
}

void SampleView::showDuplicateId() {
    std::cout << "[오류] 이미 존재하는 시료 ID입니다. 다시 입력해 주세요.\n";
}

void SampleView::showSampleList(const std::vector<Sample>& samples) {
    std::cout << "\n[시료 목록]\n";
    if (samples.empty()) {
        std::cout << "  등록된 시료가 없습니다.\n";
        return;
    }
    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(24) << "이름"
              << std::setw(16) << "평균생산시간"
              << std::setw(8)  << "수율"
              << std::setw(8)  << "재고\n";
    std::cout << std::string(64, '-') << "\n";
    for (const auto& s : samples) {
        std::cout << std::setw(8)  << s.id
                  << std::setw(24) << s.name
                  << std::setw(16) << (std::to_string(s.avgProductionTime) + " min/ea")
                  << std::setw(8)  << s.yield
                  << std::setw(8)  << (std::to_string(s.stock) + " ea") << "\n";
    }
}

void SampleView::showSearchMenu() {
    std::cout << "\n[시료 검색] 검색 기준을 선택하세요.\n";
    std::cout << " [1] ID로 검색\n";
    std::cout << " [2] 이름으로 검색\n";
    std::cout << " [3] 수율로 검색 (입력값 이상)\n";
    std::cout << " [0] 뒤로\n";
    std::cout << "선택: ";
}

void SampleView::showSearchPrompt() {
    std::cout << "검색어    : ";
}

void SampleView::showSearchResult(const std::vector<Sample>& samples) {
    std::cout << "\n[검색 결과] " << samples.size() << "건\n";
    showSampleList(samples);
}

void SampleView::showNoResults() {
    std::cout << "  검색 결과가 없습니다.\n";
}
