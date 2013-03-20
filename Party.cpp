#include <vector>
#include <cmath>

class Party {
private:
    std::vector<double> distances;
public:
    Party(std::vector<double> distances) : distances(distances) {
    }
    int getDistance(int index){
      return distances[index];
        }
    void putDistance(int index, double distance){
      distances[index] = distance;
    }
    void normalize (Setup setup){
      double normalization_term = 0.0;
      for (int i = 0; i < 8; ++i){
        distances[i] = exp(-setup.lambda*distances[i]);
        normalization_term += distances[i];
      }
      for (int i = 0; i < 8; ++i){
        distances[i] = distances[i]/normalization_term;
      }
    }
    int metric (double random_variable){
      double threshold = 0.0;
      int i = -1;
      if (random_variable < 0.00001){
        return 0;
      }
      else {
        while (random_variable > threshold){
          ++i;
          threshold += (double)getDistance(i);
        }
        return i;
      }
    }
 };
