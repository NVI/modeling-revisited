
#include <vector>

using namespace std;

int metric (int pp, double lambda, double randomx){
    vector<double> pv;
    if (pp == 1){
        pv.push_back(0.000);
        pv.push_back(0.254);
        pv.push_back(0.309);
        pv.push_back(0.267);
        pv.push_back(0.409);
        pv.push_back(0.425);
        pv.push_back(0.366);
        pv.push_back(0.570);
    }
    if (pp == 2){
        pv.push_back(0.254);
        pv.push_back(0.000);
        pv.push_back(0.164);
        pv.push_back(0.435);
        pv.push_back(0.533);
        pv.push_back(0.504);
        pv.push_back(0.368);
        pv.push_back(0.538);
    }
    if (pp == 3){
        pv.push_back(0.309);
        pv.push_back(0.164);
        pv.push_back(0.000);
        pv.push_back(0.376);
        pv.push_back(0.432);
        pv.push_back(0.382);
        pv.push_back(0.227);
        pv.push_back(0.377);
    }
    if (pp == 4){
        pv.push_back(0.267);
        pv.push_back(0.435);
        pv.push_back(0.376);
        pv.push_back(0.000);
        pv.push_back(0.151);
        pv.push_back(0.200);
        pv.push_back(0.251);
        pv.push_back(0.418);
    }
    if (pp == 5){
        pv.push_back(0.409);
        pv.push_back(0.533);
        pv.push_back(0.432);
        pv.push_back(0.151);
        pv.push_back(0.000);
        pv.push_back(0.090);
        pv.push_back(0.233);
        pv.push_back(0.329);
    }
    if (pp == 6){
        pv.push_back(0.425);
        pv.push_back(0.504);
        pv.push_back(0.382);
        pv.push_back(0.200);
        pv.push_back(0.090);
        pv.push_back(0.000);
        pv.push_back(0.163);
        pv.push_back(0.240);
    }
    if (pp == 7){
        pv.push_back(0.366);
        pv.push_back(0.368);
        pv.push_back(0.227);
        pv.push_back(0.251);
        pv.push_back(0.233);
        pv.push_back(0.163);
        pv.push_back(0.000);
        pv.push_back(0.204);
    }
    if (pp == 8){
        pv.push_back(0.570);
        pv.push_back(0.538);
        pv.push_back(0.377);
        pv.push_back(0.418);
        pv.push_back(0.329);
        pv.push_back(0.240);
        pv.push_back(0.204);
        pv.push_back(0.000);
    }
    for (int xa = 0; xa < 8; ++xa){
        pv[xa] = exp(-lambda*pv[xa]);
    }
    double psum = 0.0;
    for (int xb = 0; xb < 8; ++xb){
        psum += pv[xb];
    }
    for (int xc = 0; xc < 8; ++xc){
        pv[xc] = pv[xc]/psum;
    }
    double ht = 0;
    double xd = 0;
    if (randomx == 0){
        return 1;
    }
    else {
        while (randomx > ht){
            ht += pv[xd];
            ++xd;
        }
        return xd;
    }
}
