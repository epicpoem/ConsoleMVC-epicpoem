#pragma once
#include <istream>
#include "IController.h"
#include "../view/IApprovalView.h"
#include "../model/OrderRepository.h"
#include "../model/SampleRepository.h"

class ApprovalController : public IController {
public:
    ApprovalController(std::istream& in, IApprovalView& view,
                       OrderRepository& orderRepo, SampleRepository& sampleRepo);
    void run() override;

private:
    std::istream& in_;
    IApprovalView& view_;
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
};
