#include <cmath>

int metric (int party, double lambda, double rho){
    
    double distances [8]; /* previously vector<double> */
    
    if (party == 1){ distances = {0.000, 0.254, 0.309, 0.267, 0.409, 0.425, 0.366, 0.570};
    } else if (party == 2){ distances = {0.254, 0.000, 0.164, 0.435, 0.533, 0.504, 0.368, 0.538};
    } else if (party == 3){ distances = {0.309, 0.164, 0.000, 0.376, 0.432, 0.382, 0.227, 0.377};
    } else if (party == 4){ distances = {0.267, 0.435, 0.376, 0.000, 0.151, 0.200, 0.251, 0.418};
    } else if (party == 5){ distances = {0.409, 0.533, 0.432, 0.151, 0.000, 0.090, 0.233, 0.329};
    } else if (party == 6){ distances = {0.425, 0.504, 0.382, 0.200, 0.090, 0.000, 0.163, 0.240};
    } else if (party == 7){ distances = {0.366, 0.368, 0.227, 0.251, 0.233, 0.163, 0.000, 0.204};
    } else if (party == 8){ distances = {0.570, 0.538, 0.377, 0.418, 0.329, 0.240, 0.204, 0.000};
    } else { /* ERROR */ };
    
    double normalization_term = 0.0;
    
    for (int i = 0; i < 8; ++i){
        distances[i] = exp(-lambda*distances[i]);
        normalization_term += distances[i];
    }
    
    for (int i = 0; i < 8; ++i){
        distances[i] = distances[i]/normalization_term;
    }
    
    double threshold = 0.0;
    int i = 0;
    if (rho == 0){
        return 1;
    }
    else {
        while (rho > threshold){
            threshold += distances[i];
            ++i;
        }
        return i;
    }
}
