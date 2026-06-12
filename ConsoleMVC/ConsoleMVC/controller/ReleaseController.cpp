#include "ReleaseController.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

static std::string getCurrentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

ReleaseController::ReleaseController(std::istream& in, IReleaseView& view,
                                     IOrderRepository& orderRepo, ISampleRepository& sampleRepo)
    : in_(in), view_(view), orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

void ReleaseController::run() {
    auto confirmed = orderRepo_.getByStatus(OrderStatus::CONFIRMED);
    if (confirmed.empty()) {
        view_.showNoConfirmedOrders();
        return;
    }

    while (true) {
        view_.showConfirmedOrders(confirmed);

        std::string line;
        if (!std::getline(in_, line)) return;
        if (line == "0") return;

        int idx = -1;
        try { idx = std::stoi(line) - 1; } catch (...) {}

        if (idx < 0 || idx >= static_cast<int>(confirmed.size())) {
            view_.showInvalidInput();
            continue;
        }

        Order selected = confirmed[idx];
        selected.status = OrderStatus::RELEASE;
        orderRepo_.updateOrder(selected);
        sampleRepo_.decreaseStock(selected.sampleId, selected.quantity);

        view_.showReleaseSuccess(selected, getCurrentDateTime());

        confirmed = orderRepo_.getByStatus(OrderStatus::CONFIRMED);
        if (confirmed.empty()) return;
    }
}
