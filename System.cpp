#include "System.h"
#include "Party.h"
#include "Setup.h"

#include <map>
#include <vector>

System::System() {
}

void System::addParty(double lambda, std::vector<double> distances) {
    Party party(distances);
    party.normalize(lambda);
    parties.push_back(party);
}

Party System::getParty(int index) {
    return parties[index];
}
