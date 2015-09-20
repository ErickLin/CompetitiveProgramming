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
