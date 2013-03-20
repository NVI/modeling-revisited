#ifndef PARTY_H
#define	PARTY_H

class Party{
private:
    int distances [8];
public:
    Party(int c_distances [8]);
    int getDistance(int c_index);
    void putDistance(int c_index, double distance);
    void normalize(Setup setup);
    int metric (double random_variable);
};


#endif	/* PARTY_H */
