#include "Party.h"
#include "System.h"
#include "Setup.h"
#include "Network.h"
#include "Project.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <set>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/math/distributions.hpp>

int main(int argc, char **argv) {
    // initialization
    std::vector<std::string> filenames;
    for (int i = 1; i < argc; ++i) {
        filenames.push_back(argv[i]);
    }

    Setup setup;

    System eduskunta;
    double vihr [8] = {0.000, 0.254, 0.309, 0.267, 0.409, 0.425, 0.366, 0.570};
    eduskunta.addParty(setup.getLambda(), std::vector<double> (vihr, vihr + sizeof (vihr) / sizeof (double))); // Vihreat, index=0
    double vas [8] = {0.254, 0.000, 0.164, 0.435, 0.533, 0.504, 0.368, 0.538};
    eduskunta.addParty(setup.getLambda(), std::vector<double> (vas, vas + sizeof (vas) / sizeof (double))); // Vasemmistoliitto, index=1
    double sdp [8] = {0.309, 0.164, 0.000, 0.376, 0.432, 0.382, 0.227, 0.377};
    eduskunta.addParty(setup.getLambda(), std::vector<double> (sdp, sdp + sizeof (sdp) / sizeof (double))); // SDP, index=2
    double rkp [8] = {0.267, 0.435, 0.376, 0.000, 0.151, 0.200, 0.251, 0.418};
    eduskunta.addParty(setup.getLambda(), std::vector<double> (rkp, rkp + sizeof (rkp) / sizeof (double))); // RKP, index=3
    double kok [8] = {0.409, 0.533, 0.432, 0.151, 0.000, 0.090, 0.233, 0.329};
    eduskunta.addParty(setup.getLambda(), std::vector<double> (kok, kok + sizeof (kok) / sizeof (double))); // Kokoomus, index=4
    double kesk [8] = {0.425, 0.504, 0.382, 0.200, 0.090, 0.000, 0.163, 0.240};
    eduskunta.addParty(setup.getLambda(), std::vector<double> (kesk, kesk + sizeof (kesk) / sizeof (double))); // Keskusta, index=5
    double kd [8] = {0.366, 0.368, 0.227, 0.251, 0.233, 0.163, 0.000, 0.204};
    eduskunta.addParty(setup.getLambda(), std::vector<double> (kd, kd + sizeof (kd) / sizeof (double))); // Kristillisdemokraatit, index=6
    double ps [8] = {0.570, 0.538, 0.377, 0.418, 0.329, 0.240, 0.204, 0.000};
    eduskunta.addParty(setup.getLambda(), std::vector<double> (ps, ps + sizeof (ps) / sizeof (double))); // Perussuomalaiset, index=7

    // Boost setup
    boost::random::mt19937 prng;
    const unsigned int seed = 0; /* prng seed, variable over runs */
    prng.seed(static_cast<unsigned int> (seed));
    boost::uniform_01<> rfloat;
    boost::uniform_int<> rnode(0, (setup.getPopulation() - 1));
    boost::math::pareto_distribution<double> pareto(setup.getXm(), setup.getAlpha());

    std::vector<int> party(setup.getPopulation(), -1);
    std::vector<std::set<int> > friends(setup.getPopulation(), std::set<int>());
    Network network(party, friends);
    network.plod(setup, prng, rfloat, rnode, pareto);

    for (int i = 0; i < setup.getPopulation(); ++i) {
        network.switchParty(i, i / 200);
    }

    Bundle bundle;
    bundle.push_back(network);

    Project project(filenames, setup, eduskunta, bundle);

    std::cout << "Initialization done" << std::endl;

    // input
    // project.inputPolitics(); // optional
    // project.inputNetwork(); // optional

    // algorithm
    for (int iteration = 0; iteration < setup.getIterations(); ++iteration) {
        project.iterateBundle(prng, rfloat);
        std::cout << "Iteration:" << iteration << std::endl;
    }

    // output
    project.outputPolitics();
    project.outputNetwork();

    return 0;
}
