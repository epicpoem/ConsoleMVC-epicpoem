#pragma once
#include "Order.h"
#include <vector>
#include <optional>
#include <string>

class IOrderRepository {
public:
    virtual ~IOrderRepository() = default;
    virtual void add(const Order& order) = 0;
    virtual std::vector<Order> getAll() const = 0;
    virtual std::vector<Order> getByStatus(OrderStatus status) const = 0;
    virtual std::optional<Order> findByNo(const std::string& orderNo) const = 0;
    virtual int countByStatus(OrderStatus status) const = 0;
    virtual bool updateOrder(const Order& updated) = 0;
    virtual bool updateStatus(const std::string& orderNo, OrderStatus newStatus) = 0;
    virtual std::string generateOrderNo(const std::string& date) = 0;
};
