#pragma once
#include <istream>
#include "IController.h"
#include "../view/IReleaseView.h"
#include "../model/OrderRepository.h"

class ReleaseController : public IController {
public:
    ReleaseController(std::istream& in, IReleaseView& view, OrderRepository& orderRepo);
    void run() override;

private:
    std::istream& in_;
    IReleaseView& view_;
    OrderRepository& orderRepo_;
};
