/*
ID: Jugglebrosjr2
LANG: C++
TASK: schlnet
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
using namespace std;

set<int> getDom(vector<set<int> > &g) {
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
    /*
    for (set<int>::iterator it = d.begin(); it != d.end(); it++) {
        cout << (*it) << ' ';
    }
    cout << '\n';
    */
    if (d.size() == 1 && dominated.size() == n) {
        d.clear();
    }
    return d;
}

int main() {
    ifstream fin("schlnet.in");
    ofstream fout("schlnet.out");
    int n;
    fin >> n;
    vector<set<int> > edges(n);
    vector<set<int> > edgesInv(n);
    for (int i = 0; i < n; i++) {
        int r;
        fin >> r;
        while (r != 0) {
            edges[i].insert(r - 1);
            edgesInv[r - 1].insert(i);
            fin >> r;
        }
    }
    /*
    for (int i = 0; i < n; i++) {
        for (set<int>::iterator it = edges[i].begin(); it != edges[i].end(); it++) {
            cout << (*it) << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        for (set<int>::iterator it = edgesInv[i].begin(); it != edgesInv[i].end(); it++) {
            cout << (*it) << ' ';
        }
        cout << '\n';
    }
    */
    int d = getDom(edges).size();
    int cd = getDom(edgesInv).size();
    fout << (d == 0 ? 1 : d) << '\n';
    fout << max(d, cd) << '\n';
    return 0;
}
