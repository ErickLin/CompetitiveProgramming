#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    vvll comb(35, vll(35));
    comb[0][0] = 1;
    for (int i = 0; i <= 34; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]);
        }
    }
    int p;
    cin >> p;
    while (p--) {
        int k, n;
        cin >> k >> n;
        long long ways = 0;
        for (int num2StepPer = 1; (num2StepPer << 1) <= (n >> 1); num2StepPer++) {
            int num1StepPer = (n >> 1) - (num2StepPer << 1);
            if (num2StepPer >= num1StepPer) {
                ways += comb[num2StepPer + num1StepPer][num2StepPer] * comb[num2StepPer + num1StepPer][num2StepPer];
            }
        }
        cout << k << ' ' << ways << '\n';
    }
    return 0;
}
