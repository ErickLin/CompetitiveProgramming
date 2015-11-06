#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct team {
    int k, da, db;
};

bool cmpA(const team &a, const team &b) {
    return a.da - a.db < b.da - b.db;
}

bool cmpB(const team &a, const team &b) {
    return a.da - a.db > b.da - b.db;
}

int main() {
    int n = -1;
    while (n != 0) {
        cin >> n;
        if (n != 0) {
            int a, b;
            cin >> a >> b;
            vector<team> teamsA, teamsB, teamsC;
            for (int i = 0; i < n; i++) {
                int k, da, db;
                cin >> k >> da >> db;
                team t;
                t.k = k;
                t.da = da;
                t.db = db;
                if (da < db) {
                    teamsA.push_back(t);
                } else if (da > db) {
                    teamsB.push_back(t);
                } else {
                    teamsC.push_back(t);
                }
            }
            sort(teamsA.begin(), teamsA.end(), &cmpA);
            sort(teamsB.begin(), teamsB.end(), &cmpB);
            int totalD = 0;
            //teams closer to A prioritize getting balloons from A
            for (int i = 0; i < teamsA.size(); i++) {
                int aTaken = min(a, teamsA[i].k);
                a -= aTaken;
                teamsA[i].k -= aTaken;
                totalD += teamsA[i].da * aTaken;
                if (teamsA[i].k > 0) {
                    int bTaken = min(b, teamsA[i].k);
                    b -= bTaken;
                    teamsA[i].k -= bTaken;
                    totalD += teamsA[i].db * bTaken;
                }
            }
            //teams closer to B prioritize getting balloons from A
            for (int i = 0; i < teamsB.size(); i++) {
                int bTaken = min(b, teamsB[i].k);
                b -= bTaken;
                teamsB[i].k -= bTaken;
                totalD += teamsB[i].db * bTaken;
                if (teamsB[i].k > 0) {
                    int aTaken = min(a, teamsB[i].k);
                    a -= aTaken;
                    teamsB[i].k -= aTaken;
                    totalD += teamsB[i].da * aTaken;
                }
            }
            //teams that are equally close can choose either way
            for (int i = 0; i < teamsC.size(); i++) {
                int aTaken = min(a, teamsC[i].k);
                a -= aTaken;
                teamsC[i].k -= aTaken;
                totalD += teamsC[i].da * aTaken;
                if (teamsC[i].k > 0) {
                    int bTaken = min(b, teamsC[i].k);
                    b -= bTaken;
                    teamsC[i].k -= bTaken;
                    totalD += teamsC[i].db * bTaken;
                }
            }
            cout << totalD << '\n';
        }
    }
    return 0;
}
