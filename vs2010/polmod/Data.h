#pragma once

#include "stdafx.h"
#include "Network.h"
#include "Setup.h"
#include "System.h"

class Data {
public:
    Data(std::vector<std::string> filenames, Setup setup, System system, Bundle bundle);
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
