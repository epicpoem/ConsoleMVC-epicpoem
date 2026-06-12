#include "ProductionLineView.h"
#include <iostream>
#include <iomanip>

void ProductionLineView::showCurrentProduction(const ProductionItem* item) {
    std::cout << "\n[생산라인 조회] 현재 생산 중\n";
    std::cout << std::string(64, '-') << "\n";
    if (!item) {
        std::cout << "  현재 생산 중인 시료가 없습니다.\n";
        return;
    }
    std::cout << "  주문번호    : " << item->orderNo << "\n";
    std::cout << "  시료명      : " << item->sampleName << "\n";
    std::cout << "  주문량      : " << item->orderedQty << " ea\n";
    std::cout << "  재고        : " << item->stock << " ea\n";
    std::cout << "  부족분      : " << item->shortage << " ea\n";
    std::cout << "  실생산량    : " << item->actualProduction << " ea\n";
    std::cout << "  진행률      : " << std::fixed << std::setprecision(1)
              << (item->progressRate * 100.0) << " %\n";
    std::cout << "  완료 예정   : " << item->estimatedCompletionMin << " min\n";
}

void ProductionLineView::showWaitingQueue(const std::vector<WaitingItem>& queue) {
    std::cout << "\n[생산라인 조회] 대기 큐\n";
    std::cout << std::string(64, '-') << "\n";
    if (queue.empty()) {
        std::cout << "  대기 중인 주문이 없습니다.\n";
        return;
    }
    for (const auto& item : queue) {
        std::cout << "  [" << item.queuePosition << "] "
                  << item.orderNo << " | " << item.sampleName
                  << " | " << item.orderedQty << " ea"
                  << " | 실생산량: " << item.actualProduction << " ea"
                  << " | 예상완료: " << item.estimatedCompletionMin << " min\n";
    }
}

void ProductionLineView::showReturnPrompt() {
    std::cout << "\n[Enter] 메인 메뉴로 돌아가기...";
}
