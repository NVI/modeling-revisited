#ifndef SYSTEM_H
#define	SYSTEM_H

#include <map>
#include <vector>
#include "Party.h"

class System {
public:
    System();
    void addParty(double lambda, std::vector<double> distances);
    Party getParty(int index);
private:
    std::vector<Party> parties;
 };

#endif	/* SYSTEM_H */
