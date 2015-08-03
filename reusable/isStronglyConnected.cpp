#include <algorithm>
#include <set>
#include <stack>
#include <vector>
using namespace std;

set<int> dominatingSet(vector<set<int> > &g) {
    int n = g.size();
    set<int> d;
    set<int> dominated;
    for (int i = 0; i < n; i++) {
        if (dominated.find(i) == dominated.end()) {
            vector<bool> reachable(n);
            stack<int> s;
            s.push(i);
            while (!s.empty()) {
                int v = s.top();
                s.pop();
                for (set<int>::iterator it = g[v].begin()
                        ; it != g[v].end(); it++) {
                    if (!reachable[*it]) {
                        s.push(*it);
                        reachable[*it] = true;
                    }
                }
            }
            for (int j = 0; j < n; j++) {
                if (reachable[j]) {
                    dominated.insert(j);
                    d.erase(j);
                }
            }
            d.insert(i);
        }
    }
    if (d.size() == 1 && dominated.size() == n) {
        d.clear();
    }
    return d;
}

bool isStronglyConnected(vector<set<int> > &g) {
    vector<set<int> > gInv(g.size());
    for (int i = 0; i < g.size(); i++) {
        for (set<int>::iterator it = g[i].begin(); it != g[i].end(); it++) {
            gInv[*it].insert(i);
        }
    }
    return dominatingSet(g).size() == 0 && dominatingSet(gInv).size() == 0;
}
