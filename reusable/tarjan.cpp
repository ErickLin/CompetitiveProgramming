#include <algorithm>
#include <climits>
#include <iostream>
#include <list>
#include <stack>
#include <unordered_set>
#include <set>
#include <vector>
using namespace std;

void strongConnect(int v, vector<unordered_set<int> > &g, vector<int> &depth
        , vector<int> &lowestLink, stack<int> &s, vector<bool> &onStack
        , vector<set<int> > &components, int &counter, int &component) {
    depth[v] = counter;
    lowestLink[v] = counter;
    counter++;
    s.push(v);
    onStack[v] = true;
    int n = g.size();
    for (auto it = g[v].begin(); it != g[v].end(); it++) {
        int w = *it;
        if (depth[w] == INT_MAX) {
            strongConnect(w, g, depth, lowestLink, s, onStack
                    , components, counter, component);
            lowestLink[v] = min(lowestLink[v], lowestLink[w]);
        } else if (onStack[w]) {
            lowestLink[v] = min(lowestLink[v], depth[w]);
        }
    }
    //if root node, we have a complete strongly connected component
    if (lowestLink[v] == depth[v]) {
        set<int> newComponent;
        components.push_back(newComponent);
        int w;
        do {
            w = s.top();
            s.pop();
            onStack[w] = false;
            components[component].insert(w);
        } while (w != v);
        component++;
        counter = depth[v];
    }
}

//returns strongly connected components of a graph g as sets of vertices
//additionally, the components are sorted in reverse topological order
vector<set<int> > tarjan(vector<unordered_set<int> > &g) {
    int n = g.size();
    vector<int> depth(n), lowestLink(n);
    for (int i = 0; i < n; i++) {
        depth[i] = INT_MAX;
        lowestLink[i] = INT_MAX;
    }
    int counter = 0;
    int component = 0;
    stack<int> s; 
    vector<bool> onStack(n);
    vector<set<int> > components;
    for (int v = 0; v < n; v++) {
        if (depth[v] == INT_MAX) {
            strongConnect(v, g, depth, lowestLink, s, onStack, components, counter, component);
        }
    }
    return components;
}
