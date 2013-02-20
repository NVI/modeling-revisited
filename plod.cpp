#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/math/distributions.hpp>
#include <vector>
#include <algorithm>
#include "def.h"

graph plod (Setup setup, graph list){
    // Boost setup
    boost::mt19937 prng;
    prng.seed(static_cast<unsigned int>(setup.seed));
    boost::uniform_01<> prng_double;
    boost::uniform_int<> prng_int(0, (setup.population - 1));
    boost::math::pareto_distribution<double> pareto(setup.x_m, setup.alpha);
    
    // a Pareto variable determines the number of friendships for each node
    std::vector<int> friendships;
    for (int i = 0; i < setup.population; ++i) {
        double random_pareto = boost::math::quantile(pareto, prng_double(prng));
        int random_pareto_int = (int)random_pareto;
        friendships.push_back(random_pareto_int);
    }
    
    // determining the total number of friendships 
    int acc_connections = std::accumulate(friendships.begin(),friendships.end(),0);
    std::cout << acc_connections/2 << std::endl;
    int minimum = std::min(acc_connections/2,setup.connections_limit);

    // creating actual links
    for (int link = 0; link < minimum; ++link) {
        bool condition = true;
        while (condition == true) {
            int r[2] = {prng_int(prng), prng_int(prng)}; // two random integers
            while (r[0] == r[1]){
                r[0] = prng_int(prng);
                r[1] = prng_int(prng);
            } // r[0] != r[1]
            if (acc_connections < 2) {
                condition = false;
            }
            int established = (list[r[0]]).friends.count(r[1]);
            if (friendships[r[0]] > 0 && friendships[r[1]] > 0 && established == 0) {
                --friendships[r[0]];
                --friendships[r[1]];
                acc_connections -= 2;
                (list[r[0]]).friends.insert(r[1]);
                (list[r[1]]).friends.insert(r[0]);
                condition = false;
            }
        }
    }
    
    // returning adjacency list
    return list;
}
