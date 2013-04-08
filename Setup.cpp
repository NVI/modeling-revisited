/* 
 * File:   Setup.cpp
 * Author: Niko
 * 
 * Created on 8. huhtikuuta 2013, 1:54
 */

#include "Setup.h"

Setup::Setup() : iterations(200), population(1050), connections_limit(6300), inverse_temperature(0.1), lambda(32), alpha(1), x_m(3), seed(0), prng() {
}

int Setup::getIterations() {
    return iterations;
}

int Setup::getPopulation() {
    return population;
}
