#pragma once
#include <istream>
#include "IController.h"
#include "../view/IOrderView.h"
#include "../model/ISampleRepository.h"
#include "../model/IOrderRepository.h"

class OrderController : public IController {
public:
    OrderController(std::istream& in, IOrderView& view,
                    ISampleRepository& sampleRepo, IOrderRepository& orderRepo);
    void run() override;

private:
    std::istream& in_;
    IOrderView& view_;
    ISampleRepository& sampleRepo_;
    IOrderRepository& orderRepo_;
};
