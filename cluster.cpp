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
    for (int i = 0; i < setup.population; ++i) {
        fset.insert(i);
    }
    while (fset.empty() == false) {
        int r1 = -1;
        int g = 0;
        while (r1 == -1) {
            if (fset.count(g) == 1) {
                r1 = g;
            }
            ++g;
        }
        cset.insert(r1);
        pset.insert(r1);
        fset.erase(r1);
        std::set<int> xset = fset;
        while (pset.empty() == false) {
            int w = 0;
            int intk = -2;
            while (w != (intk + 1)) {
                if (pset.count(w) == 1) {
                    intk = w;
                }
                ++w;
            }
            for (int intl = 0; intl < setup.population; ++intl) {
                if (xset.count(intl) == 1){
                    xset.erase(intl);
                    if (cset.count(intl) == 0 && ((list[intk]).friends).count(intl) == 1 && (list[intk].party_index) == (list[intl]).party_index) {
                        double r2 = prng_distrib(prng);
                        double p = 1.0 - exp(-setup.inverse_temperature);
                        if (r2 < p) {
                            cset.insert(intl);
                            pset.insert(intl);
                            fset.erase(intl);
                        }
                    }
                }
            }
            pset.erase(intk);
        }
        clusters.push_back(cset);
        pset.clear();
        cset.clear();
    }
    int sum = 0;
    for (int i = 0; i < clusters.size(); ++i) {
        int first_index = 0;
        while (clusters[i].count(first_index) == 0) {
            ++first_index;
        }
        double rx = prng_distrib(prng);
        int r3 = metric(system[list[first_index].party_index], rx);
        for (int j = 0; j < setup.population; ++j) {
            if (clusters[i].count(j) == 1) {
                if (list[j].party_index != r3){
                    sum += 1;
                }
                (list[j]).party_index = r3;
            }
        }
    }
    std::cout << sum << std::endl;
    return list;
}
