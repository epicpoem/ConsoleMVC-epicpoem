#pragma once
#include "Sample.h"
#include <vector>
#include <optional>
#include <string>

class SampleRepository {
public:
    bool add(const Sample& sample);
    std::vector<Sample> getAll() const;
    std::optional<Sample> findById(const std::string& id) const;
    bool exists(const std::string& id) const;

private:
    std::vector<Sample> samples_;
};
