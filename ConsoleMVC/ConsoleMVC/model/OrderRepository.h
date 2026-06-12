#pragma once
#include "Order.h"
#include <vector>
#include <optional>
#include <string>

class OrderRepository {
public:
    void add(const Order& order);
    std::vector<Order> getAll() const;
    std::vector<Order> getByStatus(OrderStatus status) const;
    std::optional<Order> findByNo(const std::string& orderNo) const;
    bool updateStatus(const std::string& orderNo, OrderStatus newStatus);
    int countByStatus(OrderStatus status) const;

private:
    std::vector<Order> orders_;
    int dailySeq_{0};

public:
    std::string generateOrderNo(const std::string& date);
};
