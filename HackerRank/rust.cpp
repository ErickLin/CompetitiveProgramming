#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	long t;
	cin >> t;
	for (long T = 0; T < t; T++) {
		long n, m;
		cin >> n >> m;
		set<pair<long, long> > roads;
		for (long i = 0; i < m; i++) {
			long a, b;
			cin >> a >> b;
			a--;
			b--;
			roads.insert(make_pair(a, b));
			roads.insert(make_pair(b, a));

		}
		long s;
		cin >> s;
		s--;
		for (long i = 0; i < n; i++) {
			if (i == s) {
				continue;
			}
			if (roads.find(make_pair(s, i)) != roads.end()) {
				/*
				queue<long> q;
				vector<bool> visited(n);
				vector<long> dists(n);
				q.push(s);
				visited[s] = true;
				dists[s] = 0;
				bool found = false;
				while (!q.empty() && !found) {
					long node = q.front();
					q.pop();
					for (long j = 0; j < n && !found; j++) {
						if (!visited[j] && roads.find(make_pair(s, i)) == roads.end()) {
							dists[j] = dists[node] + 1;
							if (j == i) {
								found = true;
								cout << dists[j];
							} else {
								q.push(j);
								visited[j] = true;
							}
						}
					}
				}
				*/
				cout << "2";
			} else {
				cout << "1";
			}
			if (i < n - 1) {
				cout << ' ';
			}
		}
		cout << '\n';
	}
	return 0;
}