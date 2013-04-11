#include <vector>
#include "Project.h"
#include "Setup.h"

Project::Project(const std::string filenames [4], const Setup setup, System system, Bundle bundle) : filenames(filenames), setup(setup), system(system), bundle(bundle) {
}

int Project::getIterations() {
    return setup.getIterations();
}

void Project::inputPolitics() {
    int iterator = 0;
    std::ifstream data(filenames[0].c_str());
    std::string line;
    while (getline(data,line)){
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream,cell,',')){
            bundle.front().switchParty(iterator, atoi(cell.c_str()));
            ++iterator;
        }
    }
}

void Project::inputNetwork() {
    int iterator = 0;
    std::ifstream data(filenames[1].c_str());
    std::string line;
    while (getline(data,line)){
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream,cell,',')){
            bundle.front().addFriend(iterator, atoi(cell.c_str()));
        }
    }
}

void Project::iterateBundle(int rand) {
    Network network = bundle.back().cluster(setup, system, rand);
    bundle.push_back(network);
    
}

void Project::outputPolitics() {
    std::ofstream data;
    data.open (filenames[2].c_str());
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
    std::ofstream data;
    data.open (filenames[3].c_str());
    for (int iteratorA = 0; iteratorA < setup.getPopulation(); ++iteratorA) {
        for (std::set::iterator iteratorB = bundle.back().getFriends(iteratorA).begin(); iteratorB != bundle.back().getFriends(iteratorA).end(); ++iteratorB) {
            data << " " << *iteratorB;
            data << ",";
        }
        data << "\n";
    }
    data.close();
}

Project::Project(const Project& orig) {
}

Project::~Project() {
}

