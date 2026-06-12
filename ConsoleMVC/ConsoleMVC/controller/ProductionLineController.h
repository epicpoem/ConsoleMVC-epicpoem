#pragma once
#include <istream>
#include "IController.h"
#include "../view/IProductionLineView.h"
#include "../model/IOrderRepository.h"
#include "../model/ISampleRepository.h"
#include "../model/IClock.h"

class ProductionLineController : public IController {
public:
    ProductionLineController(std::istream& in, IProductionLineView& view,
                             IOrderRepository& orderRepo, ISampleRepository& sampleRepo,
                             IClock& clock);
    void run() override;

private:
    std::istream& in_;
    IProductionLineView& view_;
    IOrderRepository& orderRepo_;
    ISampleRepository& sampleRepo_;
    IClock& clock_;
};
