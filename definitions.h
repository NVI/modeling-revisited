
#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#include <string>
#include <vector>
#include <set>

int g_population;
double g_invtemperature;
double g_lambda;
unsigned long int g_seed1;
unsigned int g_seed2;
int iterations;

std::string filename_network_structure_input; /* file4 */
std::string filename_network_structure_output; /* file2 */
std::string filename_political_parties_input; /* file3 */
std::string filename_political_parties_output; /* file1 */

struct person {
    std::set<int> friends;
    int political_party;
} ;

typedef std::vector<std::set<int> > matrix;
typedef std::vector<person> graph;
typedef std::vector<graph> supergraph;

int metric (int pp, double lambda, double randomx);
graph cluster(int people, double invtemperature, graph adjlist2, unsigned int seed3, double lambda_pre);
graph plod (int population, int connections, graph adjlist, double alpha, double xm, unsigned long int seed1, unsigned int seed2);

#endif	/* DEFINITIONS_H */

