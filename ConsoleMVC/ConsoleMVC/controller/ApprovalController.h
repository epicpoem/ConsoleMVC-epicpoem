#pragma once
#include <istream>
#include "IController.h"
#include "../view/IApprovalView.h"
#include "../model/IOrderRepository.h"
#include "../model/ISampleRepository.h"
#include "../model/IClock.h"

class ApprovalController : public IController {
public:
    ApprovalController(std::istream& in, IApprovalView& view,
                       IOrderRepository& orderRepo, ISampleRepository& sampleRepo,
                       IClock& clock);
    void run() override;

private:
    std::istream& in_;
    IApprovalView& view_;
    IOrderRepository& orderRepo_;
    ISampleRepository& sampleRepo_;
    IClock& clock_;
};
