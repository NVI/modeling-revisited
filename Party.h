#ifndef PARTY_H
#define	PARTY_H

class Party{
private:
    int index;
    int distances [8];
public:
    Party(int c_index, int c_distances [8]);
    int getDistance(int c_index);
    void putDistance(int c_index, double distance);
};


#endif	/* PARTY_H */
