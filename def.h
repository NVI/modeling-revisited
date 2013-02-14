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
    unsigned long int seed1;
    unsigned int seed2;
};

std::string filename_network_structure_input; /* file4 */
std::string filename_network_structure_output; /* file2 */
std::string filename_political_parties_input; /* file3 */
std::string filename_political_parties_output; /* file1 */

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

typedef std::vector<std::set<int> > matrix;
typedef std::vector<Person> graph;
typedef std::vector<graph> evolutionary_path;

Party normalize (Party party, double lambda);
int metric (Party party, double random_variable);
graph cluster(System system, Setup setup, graph list, unsigned int prng_seed);
graph plod (int population, int connections, graph adjlist, double alpha, double xm, Setup setup);

#endif	/* DEF_H */
