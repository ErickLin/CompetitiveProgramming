/*
ID: Jugglebrosjr2
LANG: C++
TASK: cowcycle
*/
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

double minVariance = 100.0;
vector<int> bestF, bestR;
//int c = 0;

void updateVariance(vector<int> &f, vector<int> &r) {
    //Pruning the search
    if ((double) f[f.size() - 1] / r[0] >= (double) 3 * f[0] / r[r.size() - 1]) {
        vector<double> ratios(f.size() * r.size());
        for (int i = 0; i < f.size(); i++) {
            for (int j = 0; j < r.size(); j++) {
                ratios[i * r.size() + j] = (double) f[i] / r[j];
            }
        }
        sort(ratios.begin(), ratios.end());
        vector<double> diffs(f.size() * r.size() - 1);
        double mean = 0;
        for (int i = 0; i < diffs.size(); i++) {
            diffs[i] = ratios[i + 1] - ratios[i];
            mean += diffs[i];
        }
        mean /= diffs.size();
        double variance = 0;
        for (int i = 0; i < diffs.size(); i++) {
            variance += (diffs[i] - mean) * (diffs[i] - mean);
        }
        variance /= diffs.size();
        if (variance <= minVariance) {
            minVariance = variance;
            //cout << c << ' ' << variance << ' ' << minVariance << '\n';
            bestF = f;
            bestR = r;
        }
    }
}

void genR(int rLeft, int rOn, vector<int> &r, int rEnd
        , vector<int> &f) {
    if (rLeft == 0) {
        updateVariance(f, r);
    } else if (rOn <= rEnd) {
        genR(rLeft, rOn + 1, r, rEnd, f);
        r.push_back(rOn);
        genR(rLeft - 1, rOn + 1, r, rEnd, f);
        r.pop_back();
    }
}

void genF(int fLeft, int fOn, vector<int> &f, int fEnd
        , int numR, int r1, vector<int> &r, int r2) {
    if (fLeft == 0) {
        //Pruning the search
        if ((double) f[f.size() - 1] / r1 >= (double) 3 * f[0] / r2) {
            genR(numR, r1, r, r2, f);
        }
    } else if (fOn <= fEnd) {
        genF(fLeft, fOn + 1, f, fEnd, numR, r1, r, r2);
        f.push_back(fOn);
        genF(fLeft - 1, fOn + 1, f, fEnd, numR, r1, r, r2);
        f.pop_back();
    }
}

int main() {
    ifstream fin("cowcycle.in");
    ofstream fout("cowcycle.out");
    int numF, numR, f1, f2, r1, r2;
    fin >> numF >> numR >> f1 >> f2 >> r1 >> r2;
    vector<int> f, r;
    genF(numF, f1, f, f2, numR, r1, r, r2);
    //cout << c << '\n';
    fout << bestF[0];
    for (int i = 1; i < bestF.size(); i++) {
        fout << ' ' << bestF[i];
    }
    fout << '\n';
    fout << bestR[0];
    for (int i = 1; i < bestR.size(); i++) {
        fout << ' ' << bestR[i];
    }
    fout << '\n';
    return 0;
}
