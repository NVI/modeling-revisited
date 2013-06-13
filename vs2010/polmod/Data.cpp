#include "stdafx.h"
#include "Data.h"

#include <fstream>
#include <sstream>

Data::Data(std::vector<std::string> filenames, Setup setup, System system, Bundle bundle) : filenames(filenames), setup(setup), system(system), bundle(bundle) {
}

void Data::inputPolitics() {
    int iterator = 0;
    std::fstream stream(filenames[0].c_str(), std::fstream::in);
    std::string line;
    while (getline(stream, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream, cell, ',')) {
            bundle.front().switchParty(iterator, atoi(cell.c_str()));
            ++iterator;
        }
    }
    stream.close();
}

void Data::inputNetwork() {
    int iterator = 0;
    std::fstream stream(filenames[1].c_str(), std::fstream::in);
    std::string line;
    while (getline(stream, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream, cell, ',')) {
            bundle.front().addFriend(iterator, atoi(cell.c_str()));
        }
    }
    stream.close();
}

void Data::iterateBundle(boost::random::mt19937& prng, boost::uniform_01<>& rfloat) {
    Network network = bundle.back();
    network.cluster(setup, system, prng, rfloat);
    bundle.push_back(network);
}

void Data::outputPolitics() {
    std::fstream stream(filenames[2].c_str(), std::fstream::out);
    for (int iteratorA = 0; iteratorA < setup.getPopulation(); ++iteratorA) {
        for (int iteratorB = 0; iteratorB <= setup.getIterations(); ++iteratorB) {
            stream << bundle[iteratorB].getParty(iteratorA);
            stream << ",";
        }
        stream << "\n";
    }
    stream.close();
}

void Data::outputNetwork() {
    std::fstream stream(filenames[3].c_str(), std::fstream::out);
    for (int index = 0; index < setup.getPopulation(); ++index) {
        std::set<int> this_set = bundle.back().getFriends(index);
        for (std::set<int>::iterator it = this_set.begin(); it != this_set.end(); ++it) {
            stream << *it << ",";
        }
        stream << "\n";
    }
    stream.close();
}
