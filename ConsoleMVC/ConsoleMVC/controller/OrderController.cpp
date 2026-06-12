#include "OrderController.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

static std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d");
    return oss.str();
}

OrderController::OrderController(std::istream& in, IOrderView& view,
                                 ISampleRepository& sampleRepo, IOrderRepository& orderRepo)
    : in_(in), view_(view), sampleRepo_(sampleRepo), orderRepo_(orderRepo) {}

void OrderController::run() {
    view_.showOrderForm();

    std::string sampleId;
    while (true) {
        view_.showSampleIdPrompt();
        if (!std::getline(in_, sampleId)) return;
        if (sampleId.empty()) continue;
        if (sampleRepo_.exists(sampleId)) break;
        view_.showInvalidSampleId();
    }

    view_.showCustomerNamePrompt();
    std::string customerName;
    if (!std::getline(in_, customerName)) return;

    int qty = 0;
    while (true) {
        view_.showQuantityPrompt();
        std::string qtyStr;
        if (!std::getline(in_, qtyStr)) return;
        if (qtyStr.empty()) continue;
        try { qty = std::stoi(qtyStr); } catch (...) { qty = 0; }
        if (qty > 0) break;
        view_.showInvalidQuantity();
    }

    Order order;
    order.orderNo = orderRepo_.generateOrderNo(getCurrentDate());
    order.sampleId = sampleId;
    order.customerName = customerName;
    order.quantity = qty;
    order.status = OrderStatus::RESERVED;

    orderRepo_.add(order);
    view_.showOrderSuccess(order);
}
