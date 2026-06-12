#pragma once
#include <istream>
#include "IController.h"
#include "../view/ISampleView.h"
#include "../model/ISampleRepository.h"

class SampleController : public IController {
public:
    SampleController(std::istream& in, ISampleView& view, ISampleRepository& repo);
    void run() override;

private:
    void handleRegister();
    void handleList();
    void handleSearch();

    std::istream& in_;
    ISampleView& view_;
    ISampleRepository& repo_;
};
