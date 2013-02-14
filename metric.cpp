#include "def.h"

int metric (Party party, double random_variable){
    double threshold = 0.0;
    int i = -1;
    if (random_variable == 0){
        return 0;
    }
    else {
        while (random_variable > threshold){
            ++i;
            threshold += party.distances[i];
        }
        return i;
    }
}
