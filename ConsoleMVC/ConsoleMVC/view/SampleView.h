#pragma once
#include "ISampleView.h"

class SampleView : public ISampleView {
public:
    void showMenu() override;
    void showInvalidInput() override;
    void showRegisterPrompt() override;
    void showRegisterSuccess(const Sample& sample) override;
    void showDuplicateId() override;
    void showSampleList(const std::vector<Sample>& samples) override;
    void showSearchMenu() override;
    void showSearchResult(const std::vector<Sample>& samples) override;
    void showNoResults() override;
};
