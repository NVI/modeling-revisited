class Party {
private:
    int index;
    double distances [8];
public:
    Party(int c_index, double c_distances [8]){
      index = c_index;
      distances = c_distances;
    }
    int getDistance(int c_index){
      return distances[c_index];
        }
    void putDistance(int c_index, double distance){
      distances[c_index] = distance;
    }
 };
