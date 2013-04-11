#include "Party.h"

#include <vector>
#include <cmath>

Party::Party(std::vector<double> distances) : distances(distances) {
}

int Party::getDistance(int index){
      return distances[index];
}

void Party::putDistance(int index, double distance){
      distances[index] = distance;
}

void Party::normalize (double lambda){
      double normalization_term = 0.0;
      for (int i = 0; i < distances.size(); ++i){
        distances[i] = exp(-lambda*distances[i]);
        normalization_term += distances[i];
      }
      for (int i = 0; i < distances.size(); ++i){
        distances[i] = distances[i]/normalization_term;
      }
    }

int Party::metric (double random_variable){
      double threshold = 0.0;
      int i = -1;
      if (random_variable < 0.00001){
        return 0;
      }
      else {
        while (random_variable > threshold){
          ++i;
          threshold += distances[i];
        }
        return i;
      }
}
