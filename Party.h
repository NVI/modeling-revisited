#ifndef PARTY_H
#define	PARTY_H

class Party{
public:
    Party(std::vector<double> distances);
    int getDistance(int index);
    void putDistance(int index, double distance);
    void normalize(Setup setup);
    int metric (double random_variable);
private:
    std::vector<double> distances;
};


#endif	/* PARTY_H */
