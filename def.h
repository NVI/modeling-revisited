#ifndef DEF_H
#define	DEF_H

#include <string>
#include <vector>
#include <set>

int g_population = 1050;
double g_invtemperature = 0.1;
const double const_lambda = 32;
unsigned long int g_seed1;
unsigned int g_seed2;
int iterations = 200;

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
int metric (int pp, double lambda, double randomx);
graph cluster(int people, double invtemperature, graph adjlist2, unsigned int seed3, double lambda_pre);
graph plod (int population, int connections, graph adjlist, double alpha, double xm, unsigned long int seed1, unsigned int seed2);

#endif	/* DEF_H */
