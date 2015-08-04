/*
ID: Jugglebrosjr2
LANG: C++
TASK: tour
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
    ifstream fin("tour.in");
    ofstream fout("tour.out");
    int n, m;
    fin >> n >> m;
    map<string, int> indices;
    for (int i = 0; i < n; i++) {
        string city;
        fin >> city;
        indices[city] = i;
    }
    vector<set<int> > edges(n);
    for (int i = 0; i < m; i++) {
        string a, b;
        fin >> a >> b;
        edges[indices[a]].insert(indices[b]);
        edges[indices[b]].insert(indices[a]);
    }
    //represents the max number of cities that can be visited starting at first index,
    //visiting the first city, and ending at second index
    vector<vector<int> > dp(n, vector<int>(n));
    //base case: at most one flight from i to 0 and at most one flight from 0 to j
    dp[0][0] = 1;
    for (int i = 1; i < n; i++) {
        if (edges[i].find(0) != edges[i].end()) {
            dp[i][0] = dp[0][i] = 2;
            for (int j = 1; j < i; j++) {
                if (edges[j].find(0) != edges[j].end()) {
                    dp[i][j] = dp[j][i] = 3;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i != j && dp[i][j] > 0) {
                for (int k = min(1 + max(i, j), n - 1); k < n; k++) {
                    if (edges[i].find(k) != edges[i].end() && dp[k][j] < dp[i][j] + 1) {
                        dp[k][j] = dp[i][j] + 1;
                    }
                    if (edges[j].find(k) != edges[j].end() && dp[i][k] < dp[i][j] + 1) {
                        dp[i][k] = dp[i][j] + 1;
                    }
                }
            }
        }
    }
    if (dp[n - 1][n - 1] > 0) {
        fout << dp[n - 1][n - 1] - 1 << '\n';
    } else {
        fout << "1\n";
    }
    return 0;
}
