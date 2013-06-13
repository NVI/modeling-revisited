#include "stdafx.h"
#include "Setup.h"

Setup::Setup() : iterations(200), population(1600), connections_limit(10000), inverse_temperature(0.1), lambda(32.0), alpha(1.0), x_m(4.0) {
} // originals: iterations=200, population=1050, connections_limit=6300, invtemp=0.1, lambda=32, alpha=1, xm=3

int Setup::getIterations() const {
    return iterations;
}

int Setup::getPopulation() const {
    return population;
}

int Setup::getConnectionsLimit() const {
    return connections_limit;
}

double Setup::getInvTemperature() const {
    return inverse_temperature;
}

double Setup::getLambda() const {
    return lambda;
}

double Setup::getAlpha() const {
    return alpha;
}

double Setup::getXm() const {
    return x_m;
}
