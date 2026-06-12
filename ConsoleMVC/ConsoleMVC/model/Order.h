#pragma once
#include <string>
#include "OrderStatus.h"

struct Order {
    std::string orderNo;
    std::string sampleId;
    std::string customerName;
    int quantity{0};
    OrderStatus status{OrderStatus::RESERVED};
    int actualProduction{0};
    double totalProductionTimeMin{0.0};
};
