#pragma once
#include <istream>
#include "IController.h"
#include "../view/ISampleView.h"
#include "../model/SampleRepository.h"

class SampleController : public IController {
public:
    SampleController(std::istream& in, ISampleView& view, SampleRepository& repo);
    void run() override;

private:
    void handleRegister();
    void handleList();
    void handleSearch();

    std::istream& in_;
    ISampleView& view_;
    SampleRepository& repo_;
};
