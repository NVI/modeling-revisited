#include "Definitions.h"

System::System(Setup setup, int size) : setup(setup), size(size) {
}

void System::addParty(double* array) {
    std::vector<double> distances (array, array + size);
    Party party(distances);
    party.normalize(setup.getLambda());
    parties.push_back(party);
}

Party System::getParty(int index) const {
    return parties[index];
}
