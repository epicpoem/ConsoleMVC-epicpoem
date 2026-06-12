#include "SampleRepository.h"
#include <algorithm>

bool SampleRepository::add(const Sample& sample) {
    if (exists(sample.id)) return false;
    samples_.push_back(sample);
    return true;
}

std::vector<Sample> SampleRepository::getAll() const {
    return samples_;
}

std::optional<Sample> SampleRepository::findById(const std::string& id) const {
    auto it = std::find_if(samples_.begin(), samples_.end(),
        [&id](const Sample& s) { return s.id == id; });
    if (it == samples_.end()) return std::nullopt;
    return *it;
}

bool SampleRepository::exists(const std::string& id) const {
    return findById(id).has_value();
}

bool SampleRepository::decreaseStock(const std::string& id, int amount) {
    auto it = std::find_if(samples_.begin(), samples_.end(),
        [&id](const Sample& s) { return s.id == id; });
    if (it == samples_.end()) return false;
    it->stock = std::max(0, it->stock - amount);
    return true;
}

bool SampleRepository::increaseStock(const std::string& id, int amount) {
    auto it = std::find_if(samples_.begin(), samples_.end(),
        [&id](const Sample& s) { return s.id == id; });
    if (it == samples_.end()) return false;
    it->stock += amount;
    return true;
}
