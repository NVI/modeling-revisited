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