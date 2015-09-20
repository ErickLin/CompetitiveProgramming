#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

vector<vector<int> > preprocess(vector<int> &parent) {
    int n = parent.size();
    //max value of second index should be log(n)
    vector<vector<int> > ancestor(n, vector<int>(15));
    for (int i = 0; i < n; i++) {
        for (int j = 0; 1 << j < n; j++) {
            ancestor[i][j] = -1;
        }
    }
    for (int i = 0; i < n; i++) {
        ancestor[i][0] = parent[i];
    }
    for (int j = 1; 1 << j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (ancestor[i][j - 1] != -1) {
                ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
            }
        }
    }
    return ancestor;
}

int lca(int p, int q, vector<int> &level, vector<int> &parent
        , vector<vector<int> > &ancestor) {
    if (level[p] < level[q]) {
        int temp = p;
        p = q;
        q = temp;
    }

    //compute log(level[p])
    int lg;
    for (lg = 1; 1 << lg <= level[p]; lg++);
    lg--;

    for (int i = lg; i >= 0; i--) {
        if (level[p] - (1 << i) >= level[q]) {
            p = ancestor[p][i];
        }
    }
    if (p == q) {
        return p;
    }
    for (int i = lg; i >= 0; i--) {
        if (ancestor[p][i] != -1 && ancestor[p][i] != ancestor[q][i]) {
            p = ancestor[p][i];
            q = ancestor[q][i];
        }
    }
    return parent[p];
}

int distance(int p, int q, vector<int> &dists, vector<int> &level
        , vector<int> &parent, vector<vector<int> > &ancestor) {
    return dists[p] + dists[q] - 2 * dists[lca(p, q, level, parent, ancestor)];
}

int main() {
    int n, t;
    cin >> n >> t;
    vector<map<int, int> > edges(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        edges[a][b] = w;
        edges[b][a] = w;
    } 
    vector<int> level(n), dists(n), parent(n);
    level[0] = 0;
    dists[0] = 0;
    parent[0] = -1;
    stack<int> s;
    s.push(0);
    vector<bool> vis(n);
    vis[0] = true;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        for (auto it = edges[v].begin(); it != edges[v].end(); it++) {
            if (!vis[it->first]) {
                level[it->first] = level[v] + 1;
                dists[it->first] = dists[v] + it->second;
                parent[it->first] = v;
                s.push(it->first);
                vis[it->first] = true;
            }
        }
    }
    vector<vector<int> > ancestor = preprocess(parent);
    while (t--) {
        int k;
        cin >> k;
        map<int, int> pop;
        for (int i = 0; i < k; i++) {
            int loc;
            cin >> loc;
            loc--;
            pop[loc]++;
        }
        long long sumDist = 0;
        for (auto it = pop.begin(); it != pop.end(); it++) {
            auto it2 = it;
            it2++;
            for (; it2 != pop.end(); it2++) {
                sumDist += (long long) (it->second) * (it2->second) * distance(
                    it->first, it2->first, dists, level, parent, ancestor);
            }
        }
        cout << sumDist << '\n';
    }
    return 0;
}
