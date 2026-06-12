#pragma once
#include <istream>
#include "IController.h"
#include "../view/IApprovalView.h"
#include "../model/OrderRepository.h"
#include "../model/SampleRepository.h"
#include "../model/IClock.h"

class ApprovalController : public IController {
public:
    ApprovalController(std::istream& in, IApprovalView& view,
                       OrderRepository& orderRepo, SampleRepository& sampleRepo,
                       IClock& clock);
    void run() override;

private:
    std::istream& in_;
    IApprovalView& view_;
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
    IClock& clock_;
};
