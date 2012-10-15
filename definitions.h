
#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#include <vector>
#include <set>

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

