#include <map>
#include "Party.h"
#include "def.h"

class System {
private:
    std::map<int, Party> parties;
public:
    System(){
    }
    void addParty(Setup setup, int index, double distances [8]){
        Party party = new Party(distances);
        party.normalize(setup);
        parties.insert(index, party);
    }
    Party getParty(int index){
        return parties[index];
    }
 };

