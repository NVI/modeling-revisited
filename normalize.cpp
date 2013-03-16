#include <cmath>
#include "def.h"

Party normalize (Party party, Setup setup){
    double normalization_term = 0.0;
    for (int i = 0; i < 8; ++i){
        party.putDistance(i, exp(-setup.lambda*party.getDistance(i)));
        normalization_term += party.getDistance(i);
    }
    for (int i = 0; i < 8; ++i){
        party.putDistance(i, party.getDistance(i)/normalization_term);
    }
    return party;
}
