#ifndef SYSTEM_H
#define	SYSTEM_H

#include "Party.h"

#include <vector>

class System {
public:
    System();
    void addParty(double lambda, std::vector<double> distances);
    Party getParty(int index) const;
private:
    std::vector<Party> parties;
};

#endif	/* SYSTEM_H */
