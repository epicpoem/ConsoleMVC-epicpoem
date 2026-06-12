#pragma once
#include <istream>
#include "IController.h"
#include "../view/IProductionLineView.h"
#include "../model/OrderRepository.h"

class ProductionLineController : public IController {
public:
    ProductionLineController(std::istream& in, IProductionLineView& view,
                             OrderRepository& orderRepo);
    void run() override;

private:
    std::istream& in_;
    IProductionLineView& view_;
    OrderRepository& orderRepo_;
};
