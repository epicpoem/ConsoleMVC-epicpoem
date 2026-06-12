#pragma once
#include <istream>
#include "IController.h"
#include "../view/IReleaseView.h"
#include "../model/IOrderRepository.h"
#include "../model/ISampleRepository.h"

class ReleaseController : public IController {
public:
    ReleaseController(std::istream& in, IReleaseView& view,
                      IOrderRepository& orderRepo, ISampleRepository& sampleRepo);
    void run() override;

private:
    std::istream& in_;
    IReleaseView& view_;
    IOrderRepository& orderRepo_;
    ISampleRepository& sampleRepo_;
};
