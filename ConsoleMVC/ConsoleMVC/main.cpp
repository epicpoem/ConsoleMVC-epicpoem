#include <iostream>
#include <array>
#include "model/SampleRepository.h"
#include "model/OrderRepository.h"
#include "view/MainMenuView.h"
#include "view/SampleView.h"
#include "view/OrderView.h"
#include "view/ApprovalView.h"
#include "view/MonitoringView.h"
#include "view/ProductionLineView.h"
#include "view/ReleaseView.h"
#include "controller/IController.h"
#include "controller/MainMenuController.h"
#include "controller/SampleController.h"
#include "controller/OrderController.h"
#include "controller/ApprovalController.h"
#include "controller/MonitoringController.h"
#include "controller/ProductionLineController.h"
#include "controller/ReleaseController.h"

int main() {
    SampleRepository sampleRepo;
    OrderRepository  orderRepo;

    MainMenuView       mainMenuView;
    SampleView         sampleView;
    OrderView          orderView;
    ApprovalView       approvalView;
    MonitoringView     monitoringView;
    ProductionLineView productionLineView;
    ReleaseView        releaseView;

    SampleController       sampleCtrl(std::cin, sampleView, sampleRepo);
    OrderController        orderCtrl(std::cin, orderView, sampleRepo, orderRepo);
    ApprovalController     approvalCtrl(std::cin, approvalView, orderRepo, sampleRepo);
    MonitoringController   monitoringCtrl(std::cin, monitoringView, orderRepo, sampleRepo);
    ProductionLineController prodLineCtrl(std::cin, productionLineView, orderRepo);
    ReleaseController      releaseCtrl(std::cin, releaseView, orderRepo);

    std::array<IController*, 6> subs = {
        &sampleCtrl,
        &orderCtrl,
        &approvalCtrl,
        &monitoringCtrl,
        &prodLineCtrl,
        &releaseCtrl
    };

    MainMenuController mainCtrl(std::cin, mainMenuView, subs);
    mainCtrl.run();

    return 0;
}
