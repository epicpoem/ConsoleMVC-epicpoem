#pragma once
#include <istream>
#include "IController.h"
#include "../view/IReleaseView.h"
#include "../model/OrderRepository.h"
#include "../model/SampleRepository.h"

class ReleaseController : public IController {
public:
    ReleaseController(std::istream& in, IReleaseView& view,
                      OrderRepository& orderRepo, SampleRepository& sampleRepo);
    void run() override;

private:
    std::istream& in_;
    IReleaseView& view_;
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
};
