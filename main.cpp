#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "def.h"

int main(){
    // initialization
    struct Setup setup;
    setup.seed1 = 0;
    setup.seed2 = 0;
    
    struct Party Vihreat;
    Vihreat.index = 0;
    Vihreat.distances = {0.000, 0.254, 0.309, 0.267, 0.409, 0.425, 0.366, 0.570};
    normalize(Vihreat,setup.lambda);
    
    struct Party Vasemmisto;
    Vasemmisto.index = 1;
    Vasemmisto.distances = {0.254, 0.000, 0.164, 0.435, 0.533, 0.504, 0.368, 0.538};
    normalize(Vasemmisto,setup.lambda);
    
    struct Party SDP;
    SDP.index = 2;
    SDP.distances = {0.309, 0.164, 0.000, 0.376, 0.432, 0.382, 0.227, 0.377};
    normalize(SDP,setup.lambda);
    
    struct Party RKP;
    RKP.index = 3;
    RKP.distances = {0.267, 0.435, 0.376, 0.000, 0.151, 0.200, 0.251, 0.418};
    normalize(RKP,setup.lambda);
    
    struct Party Kokoomus;
    Kokoomus.index = 4;
    Kokoomus.distances = {0.409, 0.533, 0.432, 0.151, 0.000, 0.090, 0.233, 0.329};
    normalize(Kokoomus,setup.lambda);
    
    struct Party Keskusta;
    Keskusta.index = 5;
    Keskusta.distances = {0.425, 0.504, 0.382, 0.200, 0.090, 0.000, 0.163, 0.240};
    normalize(Keskusta,setup.lambda);
    
    struct Party KristillisD;
    KristillisD.index = 6;
    KristillisD.distances = {0.366, 0.368, 0.227, 0.251, 0.233, 0.163, 0.000, 0.204};
    normalize(KristillisD,setup.lambda);
    
    struct Party PerusS;
    PerusS.index = 7;
    PerusS.distances = {0.570, 0.538, 0.377, 0.418, 0.329, 0.240, 0.204, 0.000};
    normalize(PerusS,setup.lambda);
    
    struct System Finland;
    Finland.parties = {Vihreat, Vasemmisto, SDP, RKP, Kokoomus, Keskusta, KristillisD, PerusS};
    
    graph new_list;
    for (int i = 0; i < setup.population; ++i){
        set emptyset;
        Person citizen = {emptyset, 0};
        new_list.push_back(citizen);
    }
    
    // input
    int ip_iter = 0;
    std::ifstream ip_data(filename_political_parties_input.c_str());
    std::string line1;
    while (getline(ip_data,line1)){
        std::stringstream lineStream(line1);
        std::string cell1;
        while (getline(lineStream,cell1,',')){
            new_list[ip_iter].party_index = atoi(cell1.c_str());
            ++ip_iter;
        }
    }
    
    int in_iter = 0;
    std::ifstream in_data(filename_network_structure_input.c_str());
    std::string line2;
    while (getline(in_data,line2)){
        std::stringstream lineStream(line2);
        std::string cell2;
        while (getline(lineStream,cell2,',')){
            (new_list[in_iter].friends).insert(atoi(cell2.c_str()));
        }
    }
    
    // algorithm
    evolutionary_path game_change;
    game_change.push_back(new_list);
    for (int algo_iter = 0; algo_iter <= setup.iterations; ++algo_iter) {
        graph t_adjlist = cluster(Finland, setup, new_list, (algo_iter + 1));
        game_change.push_back(t_adjlist);
        new_list = t_adjlist;
    }
    
    // output
    std::ofstream op_data;
    op_data.open (filename_political_parties_output.c_str());
    for (int op_iter_a = 0; op_iter_a < setup.population; ++op_iter_a) {
        for (int op_iter_b = 0; op_iter_b <= setup.iterations; ++op_iter_b) {
            op_data << (((parliament[op_iter_b])[op_iter_a]).party_index);
            op_data << ",";
        }
        op_data << "\n";
    }
    op_data.close();
    
    std::ofstream on_data;
    on_data.open (filename_network_structure_output.c_str());
    for (int on_iter_a = 0; on_iter_a < setup.population; ++on_iter_a) {
        for (set::iterator on_iter_b = new_list[on_iter_a].friends.begin(); on_iter_b != new_list[on_iter_a].friends.end(); ++on_iter_b) {
            on_data << " " << *on_iter_b;
            on_data << ",";
        }
        on_data << "\n";
    }
    on_data.close();
    
    return 0;
}
