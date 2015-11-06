#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

double pow2(double num) {
    return num * num;
}

double pow4(double num) {
    return pow2(pow2(num));
}

double rnd(double num) {
    return round(num * 1000.0) / 1000.0;
}

int main() {
    double a, b, c;
    cin >> a >> b >> c;
    if (pow2(pow2(a) + pow2(b) + pow2(c)) - 2 * (pow4(a) + pow4(b) + pow4(c)) > 0.0) {
        double s2 = 0.5 * (pow2(a) + pow2(b) + pow2(c) + sqrt(3 * (pow2(pow2(a) + pow2(b) + pow2(c)) - 2 * (pow4(a) + pow4(b) + pow4(c)))));
        cout << rnd(s2 * sqrt(3) / 4.0) << '\n';
        s2 = 0.5 * (pow2(a) + pow2(b) + pow2(c) - sqrt(3 * (pow2(pow2(a) + pow2(b) + pow2(c)) - 2 * (pow4(a) + pow4(b) + pow4(c)))));
        cout << rnd(s2 * sqrt(3) / 4.0) << '\n';
    } else {
        cout << "-1.000\n";
    }
    return 0;
}
