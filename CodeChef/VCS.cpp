#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
	ios_base::sync_with_stdio(false);
	u32 t;
	cin >> t;
	for (u32 i = 0; i < t; i++) {
		u32 src, ign, trk;
		cin >> src >> ign >> trk;
		set<u32> ignored, tracked, both;
		for (u32 j = 0; j < ign; j++) {
			u32 num;
			cin >> num;
			ignored.insert(num);
		}
		for (u32 j = 0; j < trk; j++) {
			u32 num;
			cin >> num;
			tracked.insert(num);
			if (ignored.find(num) != ignored.end()) {
				both.insert(num);
			}
		}
		cout << both.size() << ' ' << (src - ignored.size()
				- tracked.size() + both.size()) << '\n';
	}
	return 0;
}