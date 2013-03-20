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
#include "Party.h"
#include "Person.h"
#include "System.h"
#include "Graph.h"

int main(){
    // initialization
    struct Setup setup;
    
    System Finland = new System();
    Finland.addParty(setup, 0, {0.000, 0.254, 0.309, 0.267, 0.409, 0.425, 0.366, 0.570}); // Vihreat
    Finland.addParty(setup, 1, {0.254, 0.000, 0.164, 0.435, 0.533, 0.504, 0.368, 0.538}); // Vasemmistoliitto
    Finland.addParty(setup, 2, {0.309, 0.164, 0.000, 0.376, 0.432, 0.382, 0.227, 0.377}); // SDP   
    Finland.addParty(setup, 3, {0.267, 0.435, 0.376, 0.000, 0.151, 0.200, 0.251, 0.418}); // RKP
    Finland.addParty(setup, 4, {0.409, 0.533, 0.432, 0.151, 0.000, 0.090, 0.233, 0.329}); // Kokoomus 
    Finland.addParty(setup, 5, {0.425, 0.504, 0.382, 0.200, 0.090, 0.000, 0.163, 0.240}); // Keskusta
    Finland.addParty(setup, 6, {0.366, 0.368, 0.227, 0.251, 0.233, 0.163, 0.000, 0.204}); // Kristillisdemokraatit
    Finland.addParty(setup, 7, {0.570, 0.538, 0.377, 0.418, 0.329, 0.240, 0.204, 0.000}); // Perussuomalaiset
    
    Graph network = new Graph(setup.population);
    
    // input
    int ip_it = 0;
    std::ifstream ip_data(setup.ppi.c_str());
    std::string line1;
    while (getline(ip_data,line1)){
        std::stringstream lineStream(line1);
        std::string cell1;
        while (getline(lineStream,cell1,',')){
            network[ip_it].switchParty(atoi(cell1.c_str()));
            ++ip_it;
        }
    }
    
    int in_it = 0;
    std::ifstream in_data(setup.nsi.c_str());
    std::string line2;
    while (getline(in_data,line2)){
        std::stringstream lineStream(line2);
        std::string cell2;
        while (getline(lineStream,cell2,',')){
            network[in_it].addFriend(atoi(cell2.c_str()));
        }
    }
    
    // algorithm
    evolutionary_path iterations;
    iterations.push_back(network);
    for (int algo_iter = 0; algo_iter <= setup.iterations; ++algo_iter) {
        graph list_iter = cluster(setup, network, Finland, (algo_iter + 1));
        iterations.push_back(list_iter);
        network = list_iter;
    }
    
    // output
    std::ofstream op_data;
    op_data.open (setup.ppo.c_str());
    for (int op_itA = 0; op_itA < setup.population; ++op_itA) {
        for (int op_itB = 0; op_itB <= setup.iterations; ++op_itB) {
            op_data << (((iterations[op_itB])[op_itA]).getParty());
            op_data << ",";
        }
        op_data << "\n";
    }
    op_data.close();
    
    std::ofstream on_data;
    on_data.open (setup.nso.c_str());
    for (int on_itA = 0; on_itA < setup.population; ++on_itA) {
        for (std::set::iterator on_itB = network[on_itA].getFriends().begin(); on_itB != network[on_itA].getFriends().end(); ++on_itB) {
            on_data << " " << *on_itB;
            on_data << ",";
        }
        on_data << "\n";
    }
    on_data.close();
    
    return 0;
}
