
graph plod (int population, int connections, graph adjlist, double alpha, double xm, unsigned long int seed1, unsigned int seed2){
    const gsl_rng_type * T;
    gsl_rng * generator;
    generator = gsl_rng_alloc (gsl_rng_mt19937);
    gsl_rng_set (generator, seed1);
    vector<int> friendships;
    for (int i = 0; i < population; ++i) {
        double rand = gsl_ran_pareto (generator, alpha, xm);
        int randint = (int)rand;
        friendships.push_back(randint);
    }
    int acc_connections = accumulate(friendships.begin(),friendships.end(),0);
    cout << acc_connections << endl;
    int minima = 0;
    if (acc_connections/2 >= connections) {
        minima = connections;
    }
    if (acc_connections/2 < connections) {
        minima = acc_connections;
    }
    boost::mt19937 rgen1;
    rgen1.seed(static_cast<unsigned int>(seed2));
    boost::uniform_int<> rdist1(0, (population - 1));
    for (int i = 0; i < minima; ++i) {
        bool cond = true;
        while (cond == true) {
            int k = rdist1(rgen1);
            int l = rdist1(rgen1);
            int sum = 0;
            for (int m = 0; m < population; ++m) {
                sum += friendships[m];
            }
            if (sum < 2) {
                cond = false;
            }
            int it = (adjlist[k]).friends.count(l);
            if (k != l && friendships[k] > 0 && friendships[l] > 0 && it == 0) {
                --friendships[k];
                --friendships[l];
                (adjlist[k]).friends.insert(l);
                (adjlist[l]).friends.insert(k);
                cond = false;
            }
        }
    }
    gsl_rng_free(generator);
    return adjlist;
}
