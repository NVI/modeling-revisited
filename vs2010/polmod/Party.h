#pragma once

#include "stdafx.h"

class Party {
public:
    Party(std::vector<double> distances);
    double getDistance(int index) const;
    void putDistance(int index, double distance);
    void normalize(double lambda);
    int metric(double random_variable) const;
private:
    std::vector<double> distances;
};
