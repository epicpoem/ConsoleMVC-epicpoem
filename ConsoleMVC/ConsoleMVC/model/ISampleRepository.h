#pragma once
#include "Sample.h"
#include <vector>
#include <optional>
#include <string>

class ISampleRepository {
public:
    virtual ~ISampleRepository() = default;
    virtual bool add(const Sample& sample) = 0;
    virtual std::vector<Sample> getAll() const = 0;
    virtual std::optional<Sample> findById(const std::string& id) const = 0;
    virtual bool exists(const std::string& id) const = 0;
    virtual bool decreaseStock(const std::string& id, int amount) = 0;
    virtual bool increaseStock(const std::string& id, int amount) = 0;
};
