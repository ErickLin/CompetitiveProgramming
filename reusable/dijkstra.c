#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
vector<int> dists(6);
vector<int> prev(6);

void dijkstra(vector<vector<int> > adj) {
	priority_queue<int> q;
	vector<int> visited(adj.size());
	fill(dists.begin(), dists.end(), -1);
	fill(visited.begin(), visited.end(), false);
	q.push(0);
	dists[0] = 0;
	prev[0] = -1;
	while (!q.empty()) {
		int node = q.top();
		q.pop();
		if (!visited[node]) {
			visited[node] = true;
			for (int i = 0; i < adj.size(); i++) {
				if (dists[i] == -1 || dists[node] + adj[node][i] < dists[i]) {
					dists[i] = dists[node] + adj[node][i];
					prev[i] = node;
					q.push(i);
				}
			}
		}
	}
}

int main() {
	vector<vector<int> > adj(6, vector<int>(6));
	adj[0][0] = 0;
	adj[0][1] = 12;
	adj[0][2] = 8;
	adj[0][3] = 43;
	adj[0][4] = 79;
	adj[0][5] = 35;
	adj[1][0] = 93;
	adj[1][1] = 0;
	adj[1][2] = 18;
	adj[1][3] = 21;
	adj[1][4] = 60;
	adj[1][5] = 33;
	adj[2][0] = 17;
	adj[2][1] = 3;
	adj[2][2] = 0;
	adj[2][3] = 37;
	adj[2][4] = 50;
	adj[2][5] = 30;
	adj[3][0] = 85;
	adj[3][1] = 10;
	adj[3][2] = 91;
	adj[3][3] = 0;
	adj[3][4] = 17;
	adj[3][5] = 7;
	adj[4][0] = 28;
	adj[4][1] = 47;
	adj[4][2] = 39;
	adj[4][3] = 14;
	adj[4][4] = 0;
	adj[4][5] = 108;
	adj[5][0] = 31;
	adj[5][1] = 7;
	adj[5][2] = 29;
	adj[5][3] = 73;
	adj[5][4] = 20;
	adj[5][5] = 0;
	dijkstra(adj);
	for (int i = 0; i < 6; i++) {
		cout << "Length: " << dists[i] << "  Prev: " << prev[i] << '\n';
	}
	return 0;
}