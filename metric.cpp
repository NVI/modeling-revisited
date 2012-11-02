#include <vector>

using namespace std;

int metric (int party, double lambda, double rho){
    vector<double> distances;
    if (party == 1){
        distances.push_back(0.000);
        distances.push_back(0.254);
        distances.push_back(0.309);
        distances.push_back(0.267);
        distances.push_back(0.409);
        distances.push_back(0.425);
        distances.push_back(0.366);
        distances.push_back(0.570);
    }
    if (party == 2){
        distances.push_back(0.254);
        distances.push_back(0.000);
        distances.push_back(0.164);
        distances.push_back(0.435);
        distances.push_back(0.533);
        distances.push_back(0.504);
        distances.push_back(0.368);
        distances.push_back(0.538);
    }
    if (party == 3){
        distances.push_back(0.309);
        distances.push_back(0.164);
        distances.push_back(0.000);
        distances.push_back(0.376);
        distances.push_back(0.432);
        distances.push_back(0.382);
        distances.push_back(0.227);
        distances.push_back(0.377);
    }
    if (party == 4){
        distances.push_back(0.267);
        distances.push_back(0.435);
        distances.push_back(0.376);
        distances.push_back(0.000);
        distances.push_back(0.151);
        distances.push_back(0.200);
        distances.push_back(0.251);
        distances.push_back(0.418);
    }
    if (party == 5){
        distances.push_back(0.409);
        distances.push_back(0.533);
        distances.push_back(0.432);
        distances.push_back(0.151);
        distances.push_back(0.000);
        distances.push_back(0.090);
        distances.push_back(0.233);
        distances.push_back(0.329);
    }
    if (party == 6){
        distances.push_back(0.425);
        distances.push_back(0.504);
        distances.push_back(0.382);
        distances.push_back(0.200);
        distances.push_back(0.090);
        distances.push_back(0.000);
        distances.push_back(0.163);
        distances.push_back(0.240);
    }
    if (party == 7){
        distances.push_back(0.366);
        distances.push_back(0.368);
        distances.push_back(0.227);
        distances.push_back(0.251);
        distances.push_back(0.233);
        distances.push_back(0.163);
        distances.push_back(0.000);
        distances.push_back(0.204);
    }
    if (party == 8){
        distances.push_back(0.570);
        distances.push_back(0.538);
        distances.push_back(0.377);
        distances.push_back(0.418);
        distances.push_back(0.329);
        distances.push_back(0.240);
        distances.push_back(0.204);
        distances.push_back(0.000);
    }
    for (int i = 0; i < 8; ++i){
        distances[i] = exp(-lambda*distances[i]);
    }
    double distances_sum = 0.0;
    for (int i = 0; i < 8; ++i){
        distances_sum += distances[i];
    }
    for (int i = 0; i < 8; ++i){
        distances[i] = distances[i]/distances_sum;
    }
    double threshold = 0.0;
    int j = 0;
    if (rho == 0){
        return 1;
    }
    else {
        while (rho > threshold){
            threshold += distances[j];
            ++j;
        }
        return j;
    }
}
