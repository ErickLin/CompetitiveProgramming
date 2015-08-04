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

int dfs(int v, vector<set<int> > &edges, vector<set<int> > &edgesBack
        , vector<bool> &vis, int numVis, bool returning) {
    int n = edges.size();
    if (v == 0 && returning) {
        //counted first city twice
        return numVis - 1;
    } else if (v == n - 1 || returning) {
        int ret = 1;
        for (set<int>::iterator it = edgesBack[v].begin(); it != edgesBack[v].end(); it++) {
            if (!vis[*it]) {
                vis[*it] = true;
                ret = max(ret, dfs(*it, edges, edgesBack, vis, numVis + 1, true));
                vis[*it] = false;
            }
        }
        return ret;
    } else if (!returning) {
        int ret = 1;
        for (set<int>::iterator it = edges[v].begin(); it != edges[v].end(); it++) {
            if (!vis[*it]) {
                vis[*it] = true;
                ret = max(ret, dfs(*it, edges, edgesBack, vis, numVis + 1, false));
                vis[*it] = false;
            }
        }
        return ret;
    }
    return 1;
}

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
    vector<set<int> > edgesBack(n);
    for (int i = 0; i < m; i++) {
        string a, b;
        fin >> a >> b;
        if (indices[a] < indices[b]) {
            edges[indices[a]].insert(indices[b]);
            edgesBack[indices[b]].insert(indices[a]);
        } else {
            edges[indices[b]].insert(indices[a]);
            edgesBack[indices[a]].insert(indices[b]);
        }
    }
    vector<bool> visited(n);
    fout << dfs(0, edges, edgesBack, visited, 1, false) << '\n';
}
