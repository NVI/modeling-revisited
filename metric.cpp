#include <cmath>
#include "def.h"

int metric (Party party, double rho){
    double threshold = 0.0;
    int i = -1;
    if (rho == 0){
        return 0;
    }
    else {
        while (rho > threshold){
            ++i;
            threshold += party.distances[i];
        }
        return i;
    }
}
