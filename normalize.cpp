#include <cmath>
#include "def.h"

Party normalize (Party party, double lambda){
    double normalization_term = 0.0;
    for (int i = 0; i < 8; ++i){
        party.distances[i] = exp(-lambda*party.distances[i]);
        normalization_term += party.distances[i];
    }
    for (int i = 0; i < 8; ++i){
        party.distances[i] = party.distances[i]/normalization_term;
    }
    return party;
}
