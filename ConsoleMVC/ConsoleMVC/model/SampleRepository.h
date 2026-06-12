#pragma once
#include "ISampleRepository.h"
#include <vector>

class SampleRepository : public ISampleRepository {
public:
    bool add(const Sample& sample) override;
    std::vector<Sample> getAll() const override;
    std::optional<Sample> findById(const std::string& id) const override;
    bool exists(const std::string& id) const override;
    bool decreaseStock(const std::string& id, int amount) override;
    bool increaseStock(const std::string& id, int amount) override;

private:
    std::vector<Sample> samples_;
};
