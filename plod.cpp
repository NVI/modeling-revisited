#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/math/distributions.hpp>
#include "def.h"

graph plod (int population, int connections, graph list, Setup setup){
    boost::mt19937 prng;
    prng.seed(static_cast<unsigned int>(setup.seed));
    boost::uniform_01<> prng_distrib;
    boost::math::pareto_distribution<double> pareto(setup.x_m, setup.alpha);
    std::vector<int> friendships;
    for (int i = 0; i < population; ++i) {
        double random_float = boost::math::quantile(pareto, prng_distrib(prng));
        int random_integer = (int)random_float;
        friendships.push_back(random_integer);
    }
    int acc_connections = std::accumulate(friendships.begin(),friendships.end(),0);
    std::cout << acc_connections << std::endl;
    int minimum = 0;
    if (acc_connections/2 >= connections) {
        minimum = connections;
    }
    if (acc_connections/2 < connections) {
        minimum = acc_connections;
    }
    boost::uniform_int<> prng_distrib_int(0, (population - 1));
    for (int i = 0; i < minimum; ++i) {
        bool condition = true;
        while (condition == true) {
            int k = prng_distrib_int(prng);
            int l = prng_distrib_int(prng);
            int sum = 0;
            for (int m = 0; m < population; ++m) {
                sum += friendships[m];
            }
            if (sum < 2) {
                condition = false;
            }
            int it = (list[k]).friends.count(l);
            if (k != l && friendships[k] > 0 && friendships[l] > 0 && it == 0) {
                --friendships[k];
                --friendships[l];
                (list[k]).friends.insert(l);
                (list[l]).friends.insert(k);
                condition = false;
            }
        }
    }
    return list;
}
