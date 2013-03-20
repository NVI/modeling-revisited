#include <vector>
#include <set>
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include "System.h"
#include "Person.h"
#include "Party.h"
#include "def.h"

#include <boost/random/uniform_int.hpp>
#include <boost/math/distributions.hpp>
#include <algorithm>

class Graph {
private:
    std::vector<Person> nodes;
public:
    Graph(int n){
        nodes = new std::vector<>(n, new Person());
    }
    Graph cluster(Setup setup, System system, unsigned int prng_seed){
        Graph graph = this;
        set fset;
        set cset;
        set pset;
        set_collection clusters;
        boost::mt19937 prng;
        prng.seed(static_cast<unsigned int>(prng_seed));
        boost::uniform_01<> prng_distrib;
        double random;
        for (int i = 0; i < setup.population; ++i) {
                fset.insert(i);
        }
        while (fset.empty() == false) {
                int choice = -1;
                int choice_iter = 0;
                while (choice == -1) {
                        if (fset.count(choice_iter) == 1) {
                                choice = choice_iter;
                        }
                        ++choice_iter;
                }
                cset.insert(choice);
                pset.insert(choice);
                fset.erase(choice);
                std::set<int> xset = fset;
                while (pset.empty() == false) {
                        int w = 0;
                        int k = -2;
                        while (w != (k + 1)) {
                                if (pset.count(w) == 1) {
                                        k = w;
                                }
                                ++w;
                        }
                        for (int l = 0; l < setup.population; ++l) {
                                if (xset.count(l) == 1){
                                        xset.erase(l);
                                        if (cset.count(l) == 0 && ((graph.nodes[k]).getFriends()).count(l) == 1 && (graph.nodes[k].getParty()) == (graph.nodes[l]).getParty()) {
                                                random = prng_distrib(prng);
                                                double p = 1.0 - exp(-setup.inverse_temperature);
                                                if (random < p) {
                                                        cset.insert(l);
                                                        pset.insert(l);
                                                        fset.erase(l);
                                                }
                                        }
                                }
                        }
                        pset.erase(k);
                }       
                clusters.push_back(cset);
                pset.clear();
                cset.clear();
        }
        int number_of_changes = 0;
        for (int i = 0; i < clusters.size(); ++i) {
                int first_index = 0;
                while (clusters[i].count(first_index) == 0) {
                        ++first_index;
                }
                random = prng_distrib(prng);
                int new_party = system.getParty(graph.nodes[first_index]).metric(random);
                for (int j = 0; j < setup.population; ++j) {
                        if (clusters[i].count(j) == 1) {
                                if (graph.nodes[j].getParty() != new_party){
                                        ++number_of_changes;
                                }
                                graph.nodes[j].switchParty(new_party);
                        }
                }
        }
        std::cout << number_of_changes << std::endl;
        return graph;
    }
    Graph plod (Setup setup){
        Graph graph = this;
        
        // Boost setup
        setup.prng.seed(static_cast<unsigned int>(setup.seed));
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
            int established = (graph[r[0]]).friends.count(r[1]);
            if (friendships[r[0]] > 0 && friendships[r[1]] > 0 && established == 0) {
                --friendships[r[0]];
                --friendships[r[1]];
                acc_connections -= 2;
                (graph[r[0]]).friends.insert(r[1]);
                (graph[r[1]]).friends.insert(r[0]);
                condition = false;
            }
        }
    }
    
    // returning adjacency list
    return graph;
}

} ;

