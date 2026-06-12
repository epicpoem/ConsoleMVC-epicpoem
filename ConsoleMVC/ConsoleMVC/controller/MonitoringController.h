#pragma once
#include <istream>
#include "IController.h"
#include "../view/IMonitoringView.h"
#include "../model/OrderRepository.h"
#include "../model/SampleRepository.h"

class MonitoringController : public IController {
public:
    MonitoringController(std::istream& in, IMonitoringView& view,
                         OrderRepository& orderRepo, SampleRepository& sampleRepo);
    void run() override;

private:
    std::istream& in_;
    IMonitoringView& view_;
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
};
