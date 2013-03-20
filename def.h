#ifndef DEF_H
#define	DEF_H

#include <boost/random/mersenne_twister.hpp>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "Party.h"
#include "Person.h"
#include "System.h"

struct Setup {
    const int iterations = 200; /* number of iterations */
    const int population = 1050; /* population count */
    const int connections_limit = 6300; /* max number of friendships */
    const double inverse_temperature = 0.1;  /* statistical parameter */
    const double lambda = 32; /* statistical parameter */
    const double alpha = 1; /* Pareto distribution shape parameter */
    const double x_m = 3; /* Pareto distribution scale (min) parameter */
    const unsigned int seed = 0; /* prng seed, variable over runs */
    const std::string nsi = "nsi"; /* filename for network structure input */
    const std::string nso = "nso"; /* filename for network structure output */
    const std::string ppi = "ppi"; /* filename for political parties input */
    const std::string ppo = "ppo"; /* filename for political parties output */
    boost::random::mt19937 prng;
};

typedef std::set<int> set;
typedef std::vector<set> set_collection;
typedef std::vector<graph> evolutionary_path;

#endif	/* DEF_H */
