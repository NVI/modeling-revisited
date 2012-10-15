/*
 * File:   main.cpp
 * Author: NVI
 *
 * Created on October 25, 2011, 2:37 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <numeric>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_01.hpp>

using namespace std;

struct person {
    set<int> friends;
    int political_party;
} ;

typedef vector<set<int> > matrix;
typedef vector<person> graph;
typedef vector<graph> supergraph;

int exponential (int pp, double lambda, double randomx){
    vector<double> pv;
    if (pp == 1){
        pv.push_back(0.000);
        pv.push_back(0.254);
        pv.push_back(0.309);
        pv.push_back(0.267);
        pv.push_back(0.409);
        pv.push_back(0.425);
        pv.push_back(0.366);
        pv.push_back(0.570);
    }
    if (pp == 2){
        pv.push_back(0.254);
        pv.push_back(0.000);
        pv.push_back(0.164);
        pv.push_back(0.435);
        pv.push_back(0.533);
        pv.push_back(0.504);
        pv.push_back(0.368);
        pv.push_back(0.538);
    }
    if (pp == 3){
        pv.push_back(0.309);
        pv.push_back(0.164);
        pv.push_back(0.000);
        pv.push_back(0.376);
        pv.push_back(0.432);
        pv.push_back(0.382);
        pv.push_back(0.227);
        pv.push_back(0.377);
    }
    if (pp == 4){
        pv.push_back(0.267);
        pv.push_back(0.435);
        pv.push_back(0.376);
        pv.push_back(0.000);
        pv.push_back(0.151);
        pv.push_back(0.200);
        pv.push_back(0.251);
        pv.push_back(0.418);
    }
    if (pp == 5){
        pv.push_back(0.409);
        pv.push_back(0.533);
        pv.push_back(0.432);
        pv.push_back(0.151);
        pv.push_back(0.000);
        pv.push_back(0.090);
        pv.push_back(0.233);
        pv.push_back(0.329);
    }
    if (pp == 6){
        pv.push_back(0.425);
        pv.push_back(0.504);
        pv.push_back(0.382);
        pv.push_back(0.200);
        pv.push_back(0.090);
        pv.push_back(0.000);
        pv.push_back(0.163);
        pv.push_back(0.240);
    }
    if (pp == 7){
        pv.push_back(0.366);
        pv.push_back(0.368);
        pv.push_back(0.227);
        pv.push_back(0.251);
        pv.push_back(0.233);
        pv.push_back(0.163);
        pv.push_back(0.000);
        pv.push_back(0.204);
    }
    if (pp == 8){
        pv.push_back(0.570);
        pv.push_back(0.538);
        pv.push_back(0.377);
        pv.push_back(0.418);
        pv.push_back(0.329);
        pv.push_back(0.240);
        pv.push_back(0.204);
        pv.push_back(0.000);
    }
    for (int xa = 0; xa < 8; ++xa){
        pv[xa] = exp(-lambda*pv[xa]);
    }
    double psum = 0.0;
    for (int xb = 0; xb < 8; ++xb){
        psum += pv[xb];
    }
    for (int xc = 0; xc < 8; ++xc){
        pv[xc] = pv[xc]/psum;
    }
    double ht = 0;
    double xd = 0;
    if (randomx == 0){
        return 1;
    }
    else {
        while (randomx > ht){
            ht += pv[xd];
            ++xd;
        }
        return xd;
    }
}

graph plod (int population, int connections, graph adjlist, double alpha, double xm, unsigned long int seed1, unsigned int seed2){
    const gsl_rng_type * T;
    gsl_rng * generator;
    generator = gsl_rng_alloc (gsl_rng_mt19937);
    gsl_rng_set (generator, seed1);
    vector<int> friendships;
    for (int i = 0; i < population; ++i) {
        double rand = gsl_ran_pareto (generator, alpha, xm);
        int randint = (int)rand;
        friendships.push_back(randint);
    }
    int acc_connections = accumulate(friendships.begin(),friendships.end(),0);
    cout << acc_connections << endl;
    int minima = 0;
    if (acc_connections/2 >= connections) {
        minima = connections;
    }
    if (acc_connections/2 < connections) {
        minima = acc_connections;
    }
    boost::mt19937 rgen1;
    rgen1.seed(static_cast<unsigned int>(seed2));
    boost::uniform_int<> rdist1(0, (population - 1));
    for (int j = 0; j < minima; ++j) {
        bool cond = true;
        while (cond == true) {
            int k = rdist1(rgen1);
            int l = rdist1(rgen1);
            int sum = 0;
            for (int m = 0; m < population; ++m) {
                sum += friendships[m];
            }
            if (sum < 2) {
                cond = false;
            }
            int it = (adjlist[k]).friends.count(l);
            if (k != l && friendships[k] > 0 && friendships[l] > 0 && it == 0) {
                --friendships[k];
                --friendships[l];
                (adjlist[k]).friends.insert(l);
                (adjlist[l]).friends.insert(k);
                cond = false;
            }
        }
    }
    gsl_rng_free(generator);
    return adjlist;
}

graph cluster(int people, double invtemperature, graph adjlist2, unsigned int seed3, double lambda_pre){
    set<int> fset;
    set<int> cset;
    set<int> pset;
    matrix clusters;
    boost::mt19937 rgen2;
    rgen2.seed(static_cast<unsigned int>(seed3));
    boost::uniform_01<> rdist2;
    for (int f = 0; f < people; ++f) {
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
        set<int> xset = fset;
        while (pset.empty() == false) {
            int w = 0;
            int intk = -2;
            while (w != (intk + 1)) {
                if (pset.count(w) == 1) {
                    intk = w;
                }
                ++w;
            }
            for (int intl = 0; intl < people; ++intl) {
                if (xset.count(intl) == 1){
                    xset.erase(intl);
                    if (cset.count(intl) == 0 && ((adjlist2[intk]).friends).count(intl) == 1 && (adjlist2[intk].political_party) == (adjlist2[intl]).political_party) {
                        double r2 = rdist2(rgen2);
                        double p = 1.0 - exp(-invtemperature);
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
        int gl = 0;
        while (clusters[h].count(gl) == 0) {
            ++gl;
        }
        double rx = rdist2(rgen2);
        int r3 = exponential(adjlist2[gl].political_party, lambda_pre, rx);
        for (int i = 0; i < people; ++i) {
            if (clusters[h].count(i) == 1) {
                if (adjlist2[i].political_party != r3){
                    sigma += 1;
                }
                (adjlist2[i]).political_party = r3;
            }
        }
    }
    cout << sigma << endl;
    return adjlist2;
}

int main(){
    int g_population = 1050;
    double g_invtemperature = 0.1;
    double g_lambda = 32;
    unsigned long int g_seed1;
    unsigned int g_seed2;
    string file1;
    string file2;
    string file3;
    string file4;
    int iterations = 200;
    cout << "Give seed1" << endl;
    cin >> g_seed1;
    cout << "Give seed2" << endl;
    cin >> g_seed2;
    cout << "Give filename for political parties output" << endl;
    cin >> file1;
    cout << "Give filename for network structure output" << endl;
    cin >> file2;
    cout << "Give filename for political parties input" << endl;
    cin >> file3;
    cout << "Give filename for network structure input" << endl;
    cin >> file4;
    graph n_adjlist;
    for (int index = 0; index < g_population; ++index){
        set<int> emptyset;
        person someone = {emptyset, 0};
        n_adjlist.push_back(someone);
    }
    int p1 = 0;
    ifstream ipdata(file3.c_str());
    string line1;
    while (getline(ipdata,line1)){
        stringstream lineStream(line1);
        string cell1;
        while (getline(lineStream,cell1,',')){
            n_adjlist[p1].political_party = atoi(cell1.c_str());
            ++p1;
        }
    }
    int p2 = 0;
    ifstream indata(file4.c_str());
    string line2;
    while (getline(indata,line2)){
        stringstream lineStream(line2);
        string cell2;
        while (getline(lineStream,cell2,',')){
            (n_adjlist[p2].friends).insert(atoi(cell2.c_str()));
        }
    }
    ofstream political;
    political.open (file1.c_str());
    supergraph parliament;
    parliament.push_back(n_adjlist);
    for (int h3 = 0; h3 <= iterations; ++h3) {
        graph t_adjlist = cluster(g_population, g_invtemperature, n_adjlist, (h3 + 1), g_lambda);
        parliament.push_back(t_adjlist);
        n_adjlist = t_adjlist;
        cout << h3 << endl;
    }
    for (int h4 = 0; h4 < g_population; ++h4) {
        for (int h5 = 0; h5 <= iterations; ++h5) {
            political << (((parliament[h5])[h4]).political_party);
            political << ",";
        }
        political << "\n";
    }
    ofstream network;
    network.open (file2.c_str());
    for (int p = 0; p < g_population; ++p) {
        for (set<int>::iterator q = n_adjlist[p].friends.begin(); q != n_adjlist[p].friends.end(); ++q) {
            network << " " << *q;
            network << ",";
        }
        network << "\n";
    }
    network.close();
    return 0;
}