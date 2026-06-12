#pragma once
#include <istream>
#include "IController.h"
#include "../view/IProductionLineView.h"
#include "../model/OrderRepository.h"
#include "../model/SampleRepository.h"
#include "../model/IClock.h"

class ProductionLineController : public IController {
public:
    ProductionLineController(std::istream& in, IProductionLineView& view,
                             OrderRepository& orderRepo, SampleRepository& sampleRepo,
                             IClock& clock);
    void run() override;

private:
    std::istream& in_;
    IProductionLineView& view_;
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
    IClock& clock_;
};
