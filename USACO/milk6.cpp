/*
ID: Jugglebrosjr2
LANG: C++
TASK: milk6
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int maxC = 20000000;
int maxM = 1000;
struct state {
    int node;
    long long df;
};

int main() {
    ifstream fin("milk6.in");
    ofstream fout("milk6.out");
    int n, m;
    fin >> n >> m;
    vector<vector<pair<long long, vector<int> > > > costs(
        n, vector<pair<long long, vector<int> > >(n)
    );
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<int> temp;
            costs[i][j] = make_pair(0, temp);
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b, w;
        fin >> a >> b >> w;
        a--;
        b--;
        //Hashes both the number of edges and the edge indices when calculating
        //total cost
        costs[a][b].first += ((long long) w * (maxM + 1) + 1)
            * (maxM + 1) * (maxM + 1) + i;
        costs[a][b].second.push_back(i + 1);
    }
    long long minCost = 0;
    int minEdges = 0;
    vector<int> indices;
    vector<vector<long long> > f(n, vector<long long>(n));
    bool canReach = true;
    while (canReach) {
        queue<state> q;
        vector<bool> visited(n);
        vector<int> prev(n);
        fill(prev.begin(), prev.end(), -1);
        struct state start;
        start.node = 0;
        start.df = LLONG_MAX;
        visited[0] = true;
        q.push(start);
        bool reached = false;
        while (!q.empty() && !reached) {
            struct state now = q.front();
            //cout << now.node << ' ' << now.df << '\n';
            if (now.node == n - 1) {
                reached = true;
                for (int i = now.node; prev[i] != -1; i = prev[i]) {
                    f[prev[i]][i] += now.df;
                    f[i][prev[i]] -= now.df;
                }
            } else {
                for (int i = 0; i < n; i++) {
                    if (!visited[i] && f[now.node][i] < costs[now.node][i].first) {
                        struct state newState;
                        newState.node = i;
                        newState.df = min(now.df, costs[now.node][i].first - f[now.node][i]);
                        visited[i] = true;
                        prev[i] = now.node;
                        q.push(newState);
                    }
                }
            }
            q.pop();
        }
        if (!reached) {
            canReach = false;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (visited[i] && !visited[j] && costs[i][j].first > 0) {
                        minCost += costs[i][j].first;
                        for (int k = 0; k < costs[i][j].second.size(); k++) {
                            minEdges++;
                            indices.push_back(costs[i][j].second[k]);
                        }
                    }
                }
            }
        }
    }
    sort(indices.begin(), indices.end());
    fout << minCost / (maxM + 1) / (maxM + 1) / (maxM + 1)
        << ' ' << minEdges << '\n';
    for (int i = 0; i < indices.size(); i++) {
        fout << indices[i] << '\n';
    }
}
