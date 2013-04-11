#ifndef SETUP_H
#define	SETUP_H

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

#endif	/* SETUP_H */
