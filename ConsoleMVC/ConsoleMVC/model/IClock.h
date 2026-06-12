#pragma once
#include <ctime>

class IClock {
public:
    virtual ~IClock() = default;
    virtual std::time_t now() const = 0;
};
