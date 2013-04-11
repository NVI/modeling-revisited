#ifndef PROJECT_H
#define	PROJECT_H

#include "Network.h"

#include <vector>
#include <string>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>

class Project {
public:
    Project(std::vector<std::string> filenames, Setup setup, System system, Bundle bundle);
    void inputPolitics();
    void inputNetwork();
    void iterateBundle(boost::random::mt19937 prng, boost::uniform_01<> rfloat);
    void outputPolitics();
    void outputNetwork();
private:
    std::vector<std::string> filenames;
    Setup setup;
    System system;
    Bundle bundle;
};

#endif	/* PROJECT_H */
