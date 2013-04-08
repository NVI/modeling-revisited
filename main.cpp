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
#include "Setup.h"
#include "Network.h"
#include "Project.h"

int main(int argc, char **argv){
    // initialization
    const std::string filenames [4] = {argv[1], argv[2], argv[3], argv[4]}; /* ppi, nsi, ppo, nso */
    
    const Setup setup = new Setup();
    
    System Finland = new System();
    Finland.addParty(setup, 0, {0.000, 0.254, 0.309, 0.267, 0.409, 0.425, 0.366, 0.570}); // Vihreat
    Finland.addParty(setup, 1, {0.254, 0.000, 0.164, 0.435, 0.533, 0.504, 0.368, 0.538}); // Vasemmistoliitto
    Finland.addParty(setup, 2, {0.309, 0.164, 0.000, 0.376, 0.432, 0.382, 0.227, 0.377}); // SDP   
    Finland.addParty(setup, 3, {0.267, 0.435, 0.376, 0.000, 0.151, 0.200, 0.251, 0.418}); // RKP
    Finland.addParty(setup, 4, {0.409, 0.533, 0.432, 0.151, 0.000, 0.090, 0.233, 0.329}); // Kokoomus 
    Finland.addParty(setup, 5, {0.425, 0.504, 0.382, 0.200, 0.090, 0.000, 0.163, 0.240}); // Keskusta
    Finland.addParty(setup, 6, {0.366, 0.368, 0.227, 0.251, 0.233, 0.163, 0.000, 0.204}); // Kristillisdemokraatit
    Finland.addParty(setup, 7, {0.570, 0.538, 0.377, 0.418, 0.329, 0.240, 0.204, 0.000}); // Perussuomalaiset
    
    Network network = new Network(setup.getPopulation());
    
    Bundle bundle = new Bundle();
    bundle.push_back(network);
    
    Project project = new Project(filenames, setup, Finland, bundle);
    
    // input
    project.inputPolitics();
    project.inputNetwork();

    // algorithm
    for (int iterator = 0; iterator <= project.getIterations(); ++iterator) {
        project.iterateBundle(iterator+1);
    }
    
    // output
    project.outputPolitics();
    project.outputNetwork();
    
    return 0;
}
