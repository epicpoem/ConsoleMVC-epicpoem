#pragma once
#include "IClock.h"

class SystemClock : public IClock {
public:
    std::time_t now() const override { return std::time(nullptr); }
};
