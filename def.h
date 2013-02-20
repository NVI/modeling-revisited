#ifndef DEF_H
#define	DEF_H

#include <string>
#include <vector>
#include <set>

struct Setup {
    const int iterations = 200;
    const int population = 1050;
    const double inverse_temperature = 0.1;
    const double lambda = 32;
    const double alpha = 1; // value???
    const double x_m = 1; // value???
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
    std::set<int> friends;
    int party_index; // used to be "political_party"
} ;

typedef std::set<int> set;
typedef std::vector<set> set_collection;
typedef std::vector<Person> graph;
typedef std::vector<graph> evolutionary_path;

Party normalize (Party party, Setup setup);
int metric (Party party, double random_variable);
graph cluster(System system, Setup setup, graph list, unsigned int prng_seed);
graph plod (int population, int connections, graph list, Setup setup);

#endif	/* DEF_H */
