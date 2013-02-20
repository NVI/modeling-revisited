#include <set>
#include <iostream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_01.hpp>
#include "def.h"

graph cluster(System system, Setup setup, graph list, unsigned int prng_seed){
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
                    if (cset.count(l) == 0 && ((list[k]).friends).count(l) == 1 && (list[k].party_index) == (list[l]).party_index) {
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
        int new_party = metric(system[list[first_index].party_index], random);
        for (int j = 0; j < setup.population; ++j) {
            if (clusters[i].count(j) == 1) {
                if (list[j].party_index != new_party){
                    ++number_of_changes;
                }
                (list[j]).party_index = new_party;
            }
        }
    }
    std::cout << number_of_changes << std::endl;
    return list;
}
