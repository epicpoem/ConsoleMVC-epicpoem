#pragma once
#include <istream>
#include "IController.h"
#include "../view/IOrderView.h"
#include "../model/SampleRepository.h"
#include "../model/OrderRepository.h"

class OrderController : public IController {
public:
    OrderController(std::istream& in, IOrderView& view,
                    SampleRepository& sampleRepo, OrderRepository& orderRepo);
    void run() override;

private:
    std::istream& in_;
    IOrderView& view_;
    SampleRepository& sampleRepo_;
    OrderRepository& orderRepo_;
};
