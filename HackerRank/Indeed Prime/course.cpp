#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <set>

using namespace std;
typedef unsigned int u32;

/*
u32 search(u32 node, u32 dist, vector<set<u32> > &g) {
	if (g[node].empty() || dist == g.size()) {
		return dist;
	} else {
		u32 lin = 0;
		for (set<u32>::iterator it = g[node].begin(); it != g[node].end(); it++) {
			lin = max(lin, search(*it, dist + 1, g));
		}
		return lin;
	}
}
*/

void visit(list<u32> &lin, u32 node, vector<set<u32> > &g, vector<u32> &visited) {
	visited[node] = 1;
	if (!g[node].empty()) {
		for (set<u32>::iterator it = g[node].begin(); it != g[node].end(); it++) {
			if (visited[*it] == 0) {
				visit(lin, *it, g, visited);
				if (lin.front() != *it) {
					lin.clear();
					return;
				}
			} else if (visited[*it] == 1) {
				//found cycle
				return;
			}
		}
	}
	visited[node] = 2;
	lin.push_front(node);
}

list<u32> topologicalSort(vector<set<u32> > &g) {
	list<u32> lin;
	u32 n = g.size();
	//0 = not visited, 1 = currently visiting, 2 = visited
	vector<u32> visited(n);
	for (u32 i = 0; i < n; i++) {
		if (visited[i] == 0) {
			visit(lin, i, g, visited);
			if (lin.front() != i) {
				lin.clear();
				return lin;
			}
		}
	}
	return lin;
}

int main() {
	u32 T;
	cin >> T;
	for (u32 t = 1; t <= T; t++) {
		u32 n, r;
		cin >> n >> r;
		vector<set<u32> > g(n);
		vector<set<u32> > invG(n);
		for (u32 i = 0; i < r; i++) {
			u32 a, b;
			cin >> a >> b;
			g[b].insert(a);
			invG[a].insert(b);
		}
		/*
		u32 ans = 0;
		bool hasSource = false;
		for (u32 i = 0; i < n; i++) {
			if (isSource[i]) {
				hasSource = true;
				ans = max(ans, search(i, 0, g));
			}
		}
		*/
		list<u32> lin = topologicalSort(g);
		cout << "Case " << t << ": ";
		if (lin.empty()) {
			cout << "Never Ends";
		} else {
			vector<u32> dist(n);
			u32 maxDist = 0;
			for (list<u32>::const_iterator it = lin.begin(); it != lin.end(); it++) {
				set<u32> prereqs = invG[*it];
				for (set<u32>::iterator it2 = prereqs.begin(); it2 != prereqs.end(); it2++) {
					dist[*it] = max(dist[*it], dist[*it2] + 1);
				}
				maxDist = max(maxDist, dist[*it]);
			}
			cout << (maxDist + 1) << " semester(s)";
		}
		cout << '\n';
	}
	return 0;
}