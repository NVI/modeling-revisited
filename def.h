#ifndef DEF_H
#define	DEF_H

#include <string>
#include <vector>
#include <set>

struct Setup {
    const int iterations = 200;
    const int population = 1050;
    const int connections_limit = 6300;
    const double inverse_temperature = 0.1;
    const double lambda = 32;
    const double alpha = 1;
    const double x_m = 3;
    unsigned int seed;
};

std::string filename_network_structure_input;
std::string filename_network_structure_output;
std::string filename_political_parties_input;
std::string filename_political_parties_output;

struct Party {
    int index;
    int distances [8];
};

struct System {
    Party parties [8];
};

struct Person {
    std::set<int> friends; // set of friendly nodes
    int party_index; // political party
} ;

typedef std::set<int> set;
typedef std::vector<set> set_collection;
typedef std::vector<Person> graph;
typedef std::vector<graph> evolutionary_path;

Party normalize (Party party, Setup setup);
int metric (Party party, double random_variable);
graph cluster(Setup setup, graph list, System system, unsigned int prng_seed);
graph plod (Setup setup, graph list);

#endif	/* DEF_H */
