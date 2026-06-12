#pragma once
#include "IOrderRepository.h"
#include <vector>

class OrderRepository : public IOrderRepository {
public:
    void add(const Order& order) override;
    std::vector<Order> getAll() const override;
    std::vector<Order> getByStatus(OrderStatus status) const override;
    std::optional<Order> findByNo(const std::string& orderNo) const override;
    int countByStatus(OrderStatus status) const override;
    bool updateOrder(const Order& updated) override;
    bool updateStatus(const std::string& orderNo, OrderStatus newStatus) override;
    std::string generateOrderNo(const std::string& date) override;

private:
    std::vector<Order> orders_;
    int dailySeq_{0};
};
