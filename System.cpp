#include <map>
#include <vector>
#include "Party.h"
#include "System.h"
#include "Setup.h"


System::System() {
}

void System::addParty(double lambda, std::vector<double> distances){
        Party party(distances);
        party.normalize(lambda);
        parties.push_back(party);
}

Party System::getParty(int index){
        return parties[index];
}
