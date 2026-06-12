#include "OrderRepository.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

void OrderRepository::add(const Order& order) {
    orders_.push_back(order);
}

std::vector<Order> OrderRepository::getAll() const {
    return orders_;
}

std::vector<Order> OrderRepository::getByStatus(OrderStatus status) const {
    std::vector<Order> result;
    for (const auto& o : orders_) {
        if (o.status == status) result.push_back(o);
    }
    return result;
}

std::optional<Order> OrderRepository::findByNo(const std::string& orderNo) const {
    auto it = std::find_if(orders_.begin(), orders_.end(),
        [&orderNo](const Order& o) { return o.orderNo == orderNo; });
    if (it == orders_.end()) return std::nullopt;
    return *it;
}

bool OrderRepository::updateStatus(const std::string& orderNo, OrderStatus newStatus) {
    auto it = std::find_if(orders_.begin(), orders_.end(),
        [&orderNo](const Order& o) { return o.orderNo == orderNo; });
    if (it == orders_.end()) return false;
    it->status = newStatus;
    return true;
}

int OrderRepository::countByStatus(OrderStatus status) const {
    return static_cast<int>(std::count_if(orders_.begin(), orders_.end(),
        [status](const Order& o) { return o.status == status; }));
}

bool OrderRepository::updateOrder(const Order& updated) {
    auto it = std::find_if(orders_.begin(), orders_.end(),
        [&updated](const Order& o) { return o.orderNo == updated.orderNo; });
    if (it == orders_.end()) return false;
    *it = updated;
    return true;
}

std::string OrderRepository::generateOrderNo(const std::string& date) {
    std::ostringstream oss;
    oss << "ORD-" << date << "-" << std::setw(4) << std::setfill('0') << ++dailySeq_;
    return oss.str();
}
