#include <set>
#include <iostream>
#include "def.h"

graph cluster(System system, Setup setup, graph list, unsigned int prng_seed){
    std::set<int> fset;
    std::set<int> cset;
    std::set<int> pset;
    matrix clusters;
    boost::mt19937 prng;
    prng.seed(static_cast<unsigned int>(prng_seed));
    boost::uniform_01<> prng_distrib;
    for (int f = 0; f < setup.population; ++f) {
        fset.insert(f);
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
    int sigma = 0;
    for (int h = 0; h < clusters.size(); ++h) {
        int a = 0;
        while (clusters[h].count(a) == 0) {
            ++a;
        }
        double rx = prng_distrib(prng);
        int r3 = metric(system[list[a].party_index], rx);
        for (int i = 0; i < setup.population; ++i) {
            if (clusters[h].count(i) == 1) {
                if (list[i].party_index != r3){
                    sigma += 1;
                }
                (list[i]).party_index = r3;
            }
        }
    }
    std::cout << sigma << std::endl;
    return list;
}
