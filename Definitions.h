#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#include <vector>
#include <string>
#include <set>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/math/distributions.hpp>

class Setup {
public:
    Setup();
    int getIterations() const;
    int getPopulation() const;
    int getConnectionsLimit() const;
    double getInvTemperature() const;
    double getLambda() const;
    double getAlpha() const;
    double getXm() const;
private:
    const int iterations; /* number of iterations */
    const int population; /* population count */
    const int connections_limit; /* max number of friendships */
    const double inverse_temperature; /* statistical parameter */
    const double lambda; /* statistical parameter */
    const double alpha; /* Pareto distribution shape parameter */
    const double x_m; /* Pareto distribution scale (min) parameter */
};

class Party {
public:
    Party(std::vector<double> distances);
    int getDistance(int index) const;
    void putDistance(int index, double distance);
    void normalize(double lambda);
    int metric(double random_variable) const;
private:
    std::vector<double> distances;
};

class System {
public:
    System(Setup setup, int size);
    void addParty(double* array);
    Party getParty(int index) const;
private:
    Setup setup;
    const int size;
    std::vector<Party> parties;
};

class Network {
public:
    Network(std::vector<int> party, std::vector<std::set<int> > friends);
    void switchParty(int my_index, int party_index);
    void addFriend(int my_index, int friend_index);
    int getParty(int my_index) const;
    std::set<int> getFriends(int my_index) const;
    void cluster(Setup& setup, System& system, boost::random::mt19937& prng, boost::uniform_01<>& rfloat);
    void plod(Setup& setup, boost::random::mt19937& prng, boost::uniform_01<>& rfloat, boost::uniform_int<>& rnode, boost::math::pareto_distribution<double>& pareto);
private:
    std::vector<int> party; // political party for each i
    std::vector<std::set<int> > friends; // set of friendly nodes for each i
};

typedef std::vector<Network> Bundle;

class Project {
public:
    Project(std::vector<std::string> filenames, Setup setup, System system, Bundle bundle);
    void inputPolitics();
    void inputNetwork();
    void iterateBundle(boost::random::mt19937& prng, boost::uniform_01<>& rfloat);
    void outputPolitics();
    void outputNetwork();
private:
    std::vector<std::string> filenames;
    Setup setup;
    System system;
    Bundle bundle;
};

#endif	/* DEFINITIONS_H */
