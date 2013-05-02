#ifndef SYSTEM_H
#define	SYSTEM_H

#include "Party.h"
#include "Setup.h"

#include <vector>

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

#endif	/* SYSTEM_H */
