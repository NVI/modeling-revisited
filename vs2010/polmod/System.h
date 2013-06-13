#pragma once

#include "stdafx.h"
#include "Party.h"
#include "Setup.h"

class System {
public:
    System(Setup setup, int size);
    void addParty(double* array);
    Party getParty(int index) const;
private:
    Setup setup;
    const int size;
    std::vector<Party> parties;
};
