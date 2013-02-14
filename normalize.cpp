#include <cmath>
#include "def.h"

Party normalize (Party party, Setup setup){
    double normalization_term = 0.0;
    for (int i = 0; i < 8; ++i){
        party.distances[i] = exp(-setup.lambda*party.distances[i]);
        normalization_term += party.distances[i];
    }
    for (int i = 0; i < 8; ++i){
        party.distances[i] = party.distances[i]/normalization_term;
    }
    return party;
}
