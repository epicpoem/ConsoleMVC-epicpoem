#pragma once
#include <istream>
#include "IController.h"
#include "../view/IMonitoringView.h"
#include "../model/IOrderRepository.h"
#include "../model/ISampleRepository.h"

class MonitoringController : public IController {
public:
    MonitoringController(std::istream& in, IMonitoringView& view,
                         IOrderRepository& orderRepo, ISampleRepository& sampleRepo);
    void run() override;

private:
    std::istream& in_;
    IMonitoringView& view_;
    IOrderRepository& orderRepo_;
    ISampleRepository& sampleRepo_;
};
