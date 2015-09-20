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
    //if root node
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

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        set<int> toVisit;
        for (int i = 0; i < k; i++) {
            int city;
            cin >> city;
            city--;
            toVisit.insert(city);
        }
        vector<unordered_set<int> > g(n);
        vector<unordered_set<int> > invG(n);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            g[a].insert(b);
            invG[b].insert(a);
        }
        vector<set<int> > components = tarjan(g);
        vector<int> inComponent(n);
        for (int i = 0; i < components.size(); i++) {
            for (auto it = components[i].begin(); it != components[i].end(); it++) {
                inComponent[*it] = i;
            }
        }
        //create a DAG with strongly connected components as vertices
        vector<set<int> > G(components.size());
        for (int i = 0; i < n; i++) {
            for (auto it = g[i].begin(); it != g[i].end(); it++) {
                if (inComponent[i] != inComponent[*it]) {
                    G[inComponent[i]].insert(inComponent[*it]);
                }
            }
        }
        vector<int> ans;
        set<int> ansComponents;
        //iterate in topologically sorted order
        for (int i = components.size() - 1; i >= 0; i--) {
            for (auto it = components[i].begin(); it != components[i].end(); it++) {
                if (toVisit.find(*it) != toVisit.end()) {
                    ans.push_back(*it + 1);
                    ansComponents.insert(i);
                }
            }
        }
        auto endIter = ansComponents.end();
        endIter--;
        int ansRootComponent = *endIter;
        set<int> ansReachable;
        ansReachable.insert(ansRootComponent);
        stack<int> ansS;
        ansS.push(ansRootComponent);
        vector<bool> vis(components.size());
        vis[ansRootComponent] = true;
        while (!ansS.empty()) {
            int comp = ansS.top();
            ansS.pop();
            for (auto it = G[comp].begin(); it != G[comp].end(); it++) {
                if (!vis[*it]) {
                    if (ansComponents.find(*it) != ansComponents.end()) {
                        ansReachable.insert(*it);
                    }
                    ansS.push(*it);
                    vis[*it] = true;
                }
            }
        }
        if (ansReachable.size() == ansComponents.size()) {
            cout << ans[0];
            for (int i = 1; i < ans.size(); i++) {
                cout << ' ' << ans[i];
            }
            cout << '\n';
        } else {
            cout << "-1\n";
        }
    }
}
