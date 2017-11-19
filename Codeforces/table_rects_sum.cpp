// 552A
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> l(n), d(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    vector<int> numLength(100001), energyLength(100001), numEnergy(201); 
    vector<vector<int> > numEnergyLength(201, vector<int>(100001));
    for (int i = 0; i < n; i++) {
        numLength[l[i]]++;
        energyLength[l[i]] += d[i];
        numEnergy[d[i]]++;
        numEnergyLength[d[i]][l[i]]++;
    }
    int ans = 20000000, prefixEnergy = 0, prefixNum = 0;
    for (int len = 100000; len >= 1; len--) {
        if (len < 100000) {
            prefixEnergy += energyLength[len + 1];
            prefixNum += numLength[len + 1];
        } 
        if (prefixEnergy >= ans) {
            break;
        }
        int usedEnergy = prefixEnergy;
        int remainingNum = n - numLength[len] - prefixNum; 
        for (int e = 1; e <= 200 && remainingNum >= numLength[len]; e++) {
            int removedLegs = min(numEnergy[e] - numEnergyLength[e][len]
                    , remainingNum - numLength[len] + 1);
            remainingNum -= removedLegs;
            usedEnergy += e * removedLegs;
            //cannot be used anymore for future iterations because already counted in prefixEnergy
            numEnergy[e] -= numEnergyLength[e][len];
        }
        if (remainingNum < numLength[len]) {
            ans = min(ans, usedEnergy);
        }
    }
    cout << ans << '\n';
    return 0;
}
