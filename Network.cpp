#include "Definitions.h"

#include <iostream>
#include <algorithm>
#include <numeric>

Network::Network(std::vector<int> party, std::vector<std::set<int> > friends) : party(party), friends(friends) {
}

void Network::switchParty(int my_index, int party_index) {
    party[my_index] = party_index;
}

void Network::addFriend(int my_index, int friend_index) {
    friends[my_index].insert(friend_index);
}

int Network::getParty(int my_index) const {
    return party[my_index];
}

std::set<int> Network::getFriends(int my_index) const {
    return friends[my_index];
}

void Network::cluster(Setup& setup, System& system, boost::random::mt19937& prng, boost::uniform_01<>& rfloat) {
    std::set<int> not_in_cluster;
    std::set<int> current_cluster;
    std::set<int> potential_expanders;
    std::vector<std::set<int> > list_of_clusters;
    double random;
    for (int i = 0; i < setup.getPopulation(); ++i) {
        not_in_cluster.insert(i);
    }
    // division into clusters 
    while (!not_in_cluster.empty()) {
        int founder = *not_in_cluster.begin();
        current_cluster.insert(founder);
        potential_expanders.insert(founder);
        not_in_cluster.erase(founder);
        while (!potential_expanders.empty()) {
            int socialite = *potential_expanders.begin();
            std::set<int> work_copy = not_in_cluster;
            for (std::set<int>::iterator it = work_copy.begin(); it != work_copy.end(); ++it) {
                int candidate = *it;
                bool conditions [3];
                conditions[0] = (!current_cluster.count(candidate)); // not yet in current cluster
                conditions[1] = (friends[socialite].count(candidate)); // they are friends
                conditions[2] = (party[socialite] == party[candidate]); // they belong to same party
                if (conditions[0] && (conditions[1] && conditions[2])) {
                    random = rfloat(prng);
                    double p = 1.0 - exp(-setup.getInvTemperature());
                    if (random < p) {
                        current_cluster.insert(candidate);
                        potential_expanders.insert(candidate);
                        not_in_cluster.erase(candidate);
                    }
                }
            }
            potential_expanders.erase(socialite);
        }
        list_of_clusters.push_back(current_cluster);
        potential_expanders.clear();
        current_cluster.clear();
    }
    // changing affiliations
    int number_of_changes = 0;
    for (int i = 0; i < list_of_clusters.size(); ++i) {
        int member = *list_of_clusters[i].begin(); // any member is enough
        random = rfloat(prng);
        int new_party = system.getParty(party[member]).metric(random);
        for (std::set<int>::iterator it = list_of_clusters[i].begin(); it != list_of_clusters[i].end(); ++it) {
            if (party[*it] != new_party) {
                ++number_of_changes;
            }
            party[*it] = new_party;
        }
    }
    std::cout << "Changes:" << number_of_changes << std::endl; // only for testing
}

void Network::plod(Setup& setup, boost::random::mt19937& prng, boost::uniform_01<>& rfloat, boost::uniform_int<>& rnode, boost::math::pareto_distribution<double>& pareto) {
    // numbers of friendships for each node taken from Pareto distribution
    std::vector<int> friendships;
    for (int i = 0; i < setup.getPopulation(); ++i) {
        double rpareto = boost::math::quantile(pareto, rfloat(prng));
        int int_rpareto = (int) rpareto;
        friendships.push_back(int_rpareto);
    }

    // determining total number of friendships 
    int acc_connections = std::accumulate(friendships.begin(), friendships.end(), 0);
    std::cout << "Connections:" << acc_connections / 2 << std::endl; // only for testing
    int min_connections = std::min(acc_connections / 2, setup.getConnectionsLimit());

    // creating actual links
    for (int link = 0; link < min_connections; ++link) {
        while (true) {
            // two random nodes
            int r[2] = {rnode(prng), rnode(prng)};
            // r[0] != r[1] required
            while (r[0] == r[1]) {
                r[0] = rnode(prng);
                r[1] = rnode(prng);
            }
            // if not enough connections left to be established
            if (acc_connections < 2) {
                break;
            }
            // if this connection has already been established
            int established = friends[r[0]].count(r[1]);
            bool friendships_left = (friendships[r[0]] > 0) && (friendships[r[1]] > 0);
            if (friendships_left && !established) {
                --friendships[r[0]];
                --friendships[r[1]];
                acc_connections -= 2;
                friends[r[0]].insert(r[1]);
                friends[r[1]].insert(r[0]);
                break;
            }
        }
    }
}
