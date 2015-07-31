/*
ID: Jugglebrosjr2
LANG: C++
TASK: milk4
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int q, p, minNum;
vector<int> ans;

void dfs(vector<int> pailsUsed, vector<int> &a, int nextInd, int pailsLeft) {
    if (pailsLeft == 0) {
        vector<bool> reached(q + 1);
        for (int j = 0; j <= q; j += pailsUsed[0]) {
            reached[j] = true;
        }
        for (int i = 1; i < pailsUsed.size() && minNum > pailsUsed.size(); i++) {
            for (int j = q; j >= 0 && minNum > pailsUsed.size(); j--) {
                if (reached[j]) {
                    for (int k = j + pailsUsed[i]; k <= q; k += pailsUsed[i]) {
                        reached[k] = true;
                        if (reached[q]) {
                            minNum = pailsUsed.size();
                            ans = pailsUsed;
                        }
                    }
                }
            }
        }
    } else if (nextInd < p && minNum > pailsUsed.size() + pailsLeft) {
        pailsUsed.push_back(a[nextInd]);
        dfs(pailsUsed, a, nextInd + 1, pailsLeft - 1);
        pailsUsed.pop_back();
        if (minNum > pailsUsed.size() + pailsLeft) {
            dfs(pailsUsed, a, nextInd + 1, pailsLeft);
        }
    }
}

int main() {
    ifstream fin("milk4.in");
    ofstream fout("milk4.out");
    fin >> q >> p;
    vector<int> a(p);
    for (int i = 0; i < p; i++) {
        fin >> a[i];
    }
    sort(a.begin(), a.end());
    minNum = p + 1;
    for (int i = 0; i < a.size(); i++) {
        if (minNum > 1 && q % a[i] == 0) {
            minNum = 1;
            ans.push_back(a[i]);
        }
    }
    for (int numPails = 2; numPails <= p && minNum > numPails; numPails++) {
        vector<int> temp;
        dfs(temp, a, 0, numPails);
    }
    fout << minNum;
    for (int i = 0; i < ans.size(); i++) {
        fout << ' ' << ans[i];
    }
    fout << '\n';
    return 0;
}
