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
#include "def.h"

using namespace std;

int main(){
    
    struct Setup setup;
    setup.seed1 = 0;
    setup.seed2 = 0;
    
    struct Party Vihreat;
    Vihreat.index = 0;
    Vihreat.distances = {0.000, 0.254, 0.309, 0.267, 0.409, 0.425, 0.366, 0.570};
    normalize(Vihreat,const_lambda);
    
    struct Party Vasemmisto;
    Vasemmisto.index = 1;
    Vasemmisto.distances = {0.254, 0.000, 0.164, 0.435, 0.533, 0.504, 0.368, 0.538};
    normalize(Vasemmisto,const_lambda);
    
    struct Party SDP;
    SDP.index = 2;
    SDP.distances = {0.309, 0.164, 0.000, 0.376, 0.432, 0.382, 0.227, 0.377};
    normalize(SDP,const_lambda);
    
    struct Party RKP;
    RKP.index = 3;
    RKP.distances = {0.267, 0.435, 0.376, 0.000, 0.151, 0.200, 0.251, 0.418};
    normalize(RKP,const_lambda);
    
    struct Party Kokoomus;
    Kokoomus.index = 4;
    Kokoomus.distances = {0.409, 0.533, 0.432, 0.151, 0.000, 0.090, 0.233, 0.329};
    normalize(Kokoomus,const_lambda);
    
    struct Party Keskusta;
    Keskusta.index = 5;
    Keskusta.distances = {0.425, 0.504, 0.382, 0.200, 0.090, 0.000, 0.163, 0.240};
    normalize(Keskusta,const_lambda);
    
    struct Party KristillisD;
    KristillisD.index = 6;
    KristillisD.distances = {0.366, 0.368, 0.227, 0.251, 0.233, 0.163, 0.000, 0.204};
    normalize(KristillisD,const_lambda);
    
    struct Party PerusS;
    PerusS.index = 7;
    PerusS.distances = {0.570, 0.538, 0.377, 0.418, 0.329, 0.240, 0.204, 0.000};
    normalize(PerusS,const_lambda);
    
    struct System Finland;
    Finland.parties = {Vihreat, Vasemmisto, SDP, RKP, Kokoomus, Keskusta, KristillisD, PerusS};
    
    graph n_adjlist;
    for (int i = 0; i < setup.population; ++i){
        set<int> emptyset;
        Person someone = {emptyset, 0};
        n_adjlist.push_back(someone);
    }
    int p1 = 0;
    ifstream ipdata(file3.c_str());
    string line1;
    while (getline(ipdata,line1)){
        stringstream lineStream(line1);
        string cell1;
        while (getline(lineStream,cell1,',')){
            n_adjlist[p1].party_index = atoi(cell1.c_str());
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
    evolutionary_path parliament;
    parliament.push_back(n_adjlist);
    for (int i = 0; i <= iterations; ++i) {
        graph t_adjlist = cluster(Finland, setup, n_adjlist, (i + 1));
        parliament.push_back(t_adjlist);
        n_adjlist = t_adjlist;
        cout << i << endl;
    }
    for (int i = 0; i < setup.population; ++i) {
        for (int j = 0; j <= iterations; ++j) {
            political << (((parliament[j])[i]).party_index);
            political << ",";
        }
        political << "\n";
    }
    ofstream network;
    network.open (file2.c_str());
    for (int i = 0; i < setup.population; ++i) {
        for (set<int>::iterator q = n_adjlist[i].friends.begin(); q != n_adjlist[i].friends.end(); ++q) {
            network << " " << *q;
            network << ",";
        }
        network << "\n";
    }
    network.close();
    return 0;
}