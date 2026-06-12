#include "MainMenuView.h"
#include <iostream>

void MainMenuView::showMenu() {
    std::cout << "\n========================================\n";
    std::cout << "   반도체 시료 생산주문관리 시스템\n";
    std::cout << "========================================\n";
    std::cout << " [1] 시료 관리\n";
    std::cout << " [2] 시료 주문\n";
    std::cout << " [3] 주문 승인/거절\n";
    std::cout << " [4] 모니터링\n";
    std::cout << " [5] 생산라인 조회\n";
    std::cout << " [6] 출고 처리\n";
    std::cout << " [0] 종료\n";
    std::cout << "========================================\n";
    std::cout << "선택: ";
}

void MainMenuView::showInvalidInput() {
    std::cout << "[오류] 유효하지 않은 입력입니다. 다시 입력해 주세요.\n";
}
