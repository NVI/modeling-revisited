#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
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
#include "definitions.h"

using namespace std;

int main(){
    graph n_adjlist;
    for (int i = 0; i < g_population; ++i){
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
    for (int i = 0; i <= iterations; ++i) {
        graph t_adjlist = cluster(g_population, g_invtemperature, n_adjlist, (i + 1), g_lambda);
        parliament.push_back(t_adjlist);
        n_adjlist = t_adjlist;
        cout << i << endl;
    }
    for (int i = 0; i < g_population; ++i) {
        for (int j = 0; j <= iterations; ++j) {
            political << (((parliament[j])[i]).political_party);
            political << ",";
        }
        political << "\n";
    }
    ofstream network;
    network.open (file2.c_str());
    for (int i = 0; i < g_population; ++i) {
        for (set<int>::iterator q = n_adjlist[i].friends.begin(); q != n_adjlist[i].friends.end(); ++q) {
            network << " " << *q;
            network << ",";
        }
        network << "\n";
    }
    network.close();
    return 0;
}