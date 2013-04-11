#include "Setup.h"

Setup::Setup() : iterations(200), population(1600), connections_limit(10000), inverse_temperature(0.1), lambda(32.0), alpha(1.0), x_m(4.0) {
} // originals: iterations=200, population=1050, connections_limit=6300, invtemp=0.1, lambda=32, alpha=1, xm=3

int Setup::getIterations() {
    return iterations;
}

int Setup::getPopulation() {
    return population;
}

int Setup::getConnectionsLimit() {
    return connections_limit;
}

double Setup::getInvTemperature() {
    return inverse_temperature;
}

double Setup::getLambda() {
    return lambda;
}

double Setup::getAlpha() {
    return alpha;
}

double Setup::getXm() {
    return x_m;
}
