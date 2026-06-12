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
                                 SampleRepository& sampleRepo, OrderRepository& orderRepo)
    : in_(in), view_(view), sampleRepo_(sampleRepo), orderRepo_(orderRepo) {}

void OrderController::run() {
    view_.showOrderForm();

    std::string sampleId;
    if (!std::getline(in_, sampleId)) return;

    if (!sampleRepo_.exists(sampleId)) {
        view_.showInvalidSampleId();
        return;
    }

    view_.showCustomerNamePrompt();
    std::string customerName;
    if (!std::getline(in_, customerName)) return;

    view_.showQuantityPrompt();
    std::string qtyStr;
    if (!std::getline(in_, qtyStr)) return;
    int qty = 0;
    try { qty = std::stoi(qtyStr); } catch (...) {}

    if (qty <= 0) {
        view_.showInvalidQuantity();
        return;
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
