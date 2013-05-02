#ifndef NETWORK_H
#define	NETWORK_H

#include "Setup.h"
#include "System.h"

#include <set>
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/math/distributions.hpp>

class Network {
public:
    Network(std::vector<int> party, std::vector<std::set<int> > friends);
    void switchParty(int my_index, int party_index);
    void addFriend(int my_index, int friend_index);
    int getParty(int my_index) const;
    std::set<int> getFriends(int my_index) const;
    void cluster(Setup& setup, System& system, boost::random::mt19937& prng, boost::uniform_01<>& rfloat);
    void plod(Setup& setup, boost::random::mt19937& prng, boost::uniform_01<>& rfloat, boost::uniform_int<>& rnode, boost::math::pareto_distribution<double>& pareto);
private:
    std::vector<int> party; // political party for each i
    std::vector<std::set<int> > friends; // set of friendly nodes for each i
};

typedef std::vector<Network> Bundle;

#endif	/* GRAPH_H */
