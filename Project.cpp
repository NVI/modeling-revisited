#include "Definitions.h"

#include <fstream>
#include <sstream>
#include <iostream>

Project::Project(std::vector<std::string> filenames, Setup setup, System system, Bundle bundle) : filenames(filenames), setup(setup), system(system), bundle(bundle) {
}

void Project::inputPolitics() {
    int iterator = 0;
    std::fstream data(filenames[0].c_str(), std::fstream::in);
    std::string line;
    while (getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream, cell, ',')) {
            bundle.front().switchParty(iterator, atoi(cell.c_str()));
            ++iterator;
        }
    }
    data.close();
}

void Project::inputNetwork() {
    int iterator = 0;
    std::fstream data(filenames[1].c_str(), std::fstream::in);
    std::string line;
    while (getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream, cell, ',')) {
            bundle.front().addFriend(iterator, atoi(cell.c_str()));
        }
    }
    data.close();
}

void Project::iterateBundle(boost::random::mt19937& prng, boost::uniform_01<>& rfloat) {
    Network network = bundle.back();
    network.cluster(setup, system, prng, rfloat);
    bundle.push_back(network);
}

void Project::outputPolitics() {
    std::fstream data(filenames[2].c_str(), std::fstream::out);
    for (int iteratorA = 0; iteratorA < setup.getPopulation(); ++iteratorA) {
        for (int iteratorB = 0; iteratorB <= setup.getIterations(); ++iteratorB) {
            data << bundle[iteratorB].getParty(iteratorA);
            data << ",";
        }
        data << "\n";
    }
    data.close();
}

void Project::outputNetwork() {
    std::fstream data(filenames[3].c_str(), std::fstream::out);
    for (int index = 0; index < setup.getPopulation(); ++index) {
        std::set<int> this_set = bundle.back().getFriends(index);
        for (std::set<int>::iterator it = this_set.begin(); it != this_set.end(); ++it) {
            data << *it << ",";
        }
        data << "\n";
    }
    data.close();
}
