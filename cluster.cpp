
graph cluster(int people, double invtemperature, graph adjlist2, unsigned int seed3, double lambda_pre){
    set<int> fset;
    set<int> cset;
    set<int> pset;
    matrix clusters;
    boost::mt19937 rgen2;
    rgen2.seed(static_cast<unsigned int>(seed3));
    boost::uniform_01<> rdist2;
    for (int f = 0; f < people; ++f) {
        fset.insert(f);
    }
    while (fset.empty() == false) {
        int r1 = -1;
        int g = 0;
        while (r1 == -1) {
            if (fset.count(g) == 1) {
                r1 = g;
            }
            ++g;
        }
        cset.insert(r1);
        pset.insert(r1);
        fset.erase(r1);
        set<int> xset = fset;
        while (pset.empty() == false) {
            int w = 0;
            int intk = -2;
            while (w != (intk + 1)) {
                if (pset.count(w) == 1) {
                    intk = w;
                }
                ++w;
            }
            for (int intl = 0; intl < people; ++intl) {
                if (xset.count(intl) == 1){
                    xset.erase(intl);
                    if (cset.count(intl) == 0 && ((adjlist2[intk]).friends).count(intl) == 1 && (adjlist2[intk].political_party) == (adjlist2[intl]).political_party) {
                        double r2 = rdist2(rgen2);
                        double p = 1.0 - exp(-invtemperature);
                        if (r2 < p) {
                            cset.insert(intl);
                            pset.insert(intl);
                            fset.erase(intl);
                        }
                    }
                }
            }
            pset.erase(intk);
        }
        clusters.push_back(cset);
        pset.clear();
        cset.clear();
    }
    int sigma = 0;
    for (int h = 0; h < clusters.size(); ++h) {
        int gl = 0;
        while (clusters[h].count(gl) == 0) {
            ++gl;
        }
        double rx = rdist2(rgen2);
        int r3 = metric(adjlist2[gl].political_party, lambda_pre, rx);
        for (int i = 0; i < people; ++i) {
            if (clusters[h].count(i) == 1) {
                if (adjlist2[i].political_party != r3){
                    sigma += 1;
                }
                (adjlist2[i]).political_party = r3;
            }
        }
    }
    cout << sigma << endl;
    return adjlist2;
}
