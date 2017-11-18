#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;

struct state {
    int node;
    int depth;
};
/*
struct state {
    int node;
    int steps = 0;
    unsigned long long visited = 0;
    int numVisited = 0;
};
*/

class WalkOverATree {
    public:
        int maxNodesVisited(vector<int> parent, int L) {
            int n = parent.size() + 1;
            vector<set<int> > children(n);
            for (int i = 0; i < parent.size(); i++) {
                children[parent[i]].insert(i + 1);
            }
            stack<state> s;
            state temp;
            temp.node = 0;
            temp.depth = 0;
            s.push(temp);
            vector<bool> visited(n);
            visited[0] = true;
            int maxDepth = 0;
            while (!s.empty()) {
                state cur = s.top();
                s.pop();
                for (auto it = children[cur.node].begin(); it != children[cur.node].end(); it++) {
                    if (!visited[*it]) {
                        state add;
                        add.node = *it;
                        add.depth = cur.depth + 1;
                        s.push(add);
                        visited[*it] = true;
                        maxDepth = max(maxDepth, add.depth);
                    }
                }
            }
            int maxVis;
            if (L < maxDepth) {
                maxVis = L + 1;
            } else {
                maxVis = min(n, maxDepth + ((L - maxDepth) >> 1) + 1);
            }
            return maxVis;
            /*
            stack<struct state> s;
            struct state temp;
            temp.node = 0;
            temp.steps = 0;
            temp.visited = 1ULL << 0;
            temp.numVisited = 1;
            s.push(temp);
            int maxNumVisited = 1;
            while (!s.empty() && maxNumVisited <= L) {
                struct state now = s.top();
                s.pop();
                //cout << now.node << ' ' << now.steps << '\n';
                if (now.steps < L) {
                    for (set<int>::iterator it = children[now.node].begin(); it != children[now.node].end(); it++) {
                        struct state newState;
                        newState.node = *it;
                        newState.steps = now.steps + 1;
                        if (!(now.visited & (1ULL << *it))) {
                            newState.visited = now.visited | (1ULL << *it);
                            newState.numVisited = now.numVisited + 1;
                            maxNumVisited = max(maxNumVisited, newState.numVisited);
                        }
                        s.push(newState);
                    }
                    if (now.node > 0) {
                        struct state newState;
                        newState.node = parent[now.node - 1];
                        newState.steps = now.steps + 1;
                        newState.visited = now.visited;
                        newState.numVisited = now.numVisited;
                        s.push(newState);
                    }
                }
            }
            return maxNumVisited;
            */
        }
};

int main() {
    WalkOverATree a;
    cout << a.maxNodesVisited({0, 0}, 2) << '\n';
    cout << a.maxNodesVisited({0, 0}, 3) << '\n';
    cout << a.maxNodesVisited({0, 1, 2, 3}, 2) << '\n';
    cout << a.maxNodesVisited({0,0,0,0,2,4,2,3,1}, 1) << '\n';
    cout << a.maxNodesVisited({0,0,1,2,3,2,3,1,3,0,1,8,6,8,0,5,15,0,9}, 4) << '\n';
    cout << a.maxNodesVisited({0,0,0,1,1,3,5,1,4,5,2,2,10,5,10,10,11,13,8,3,18,15,20,20,23,8,11,26,4}, 26) << '\n';
    cout << a.maxNodesVisited({0, 0, 2, 0}, 100) << '\n';
    cout << a.maxNodesVisited({0, 0, 2}, 4) << '\n';
}
