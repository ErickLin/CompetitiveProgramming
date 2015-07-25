#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int u32;

bool allTrue(map<u32, bool> &m) {
	for (map<u32, bool>::iterator i = m.begin(); i != m.end(); i++) {
		if (!(i->second)) {
			return false;
		}
	}
	return true;
}

int main() {
	u32 T;
	cin >> T;
	for (u32 t = 1; t <= T; t++) {
		u32 c, d, v;
		cin >> c >> d >> v;
		set<u32> denominations;
		vector<bool> reachable(v + 1);
		fill(reachable.begin(), reachable.end(), false);
		reachable[0] = true;
		for (size_t i = 0; i < d; i++) {
			u32 value;
			cin >> value;
			denominations.insert(value);
			for (int j = v; j >= 0; j--) {
				if (j + value <= v && reachable[j]) {
					reachable[j + value] = true;
				}
			}
			/*
			for (size_t i = 0; i <= v; i++) {
				cout << reachable[i] << ' ';
			}
			cout << '\n';
			*/
		}
		bool allReach = true;
		for (size_t i = 0; i <= v; i++) {
			if (!reachable[i]) {
				allReach = false;
			}
		}
		if (allReach) {
			cout << "Case #" << t << ": 0\n";
			continue;
		}
		map<u32, set<u32> > possible;
		map<u32, bool> satisfied;
		for (size_t i = 0; i <= v; i++) {
			if (!reachable[i]) {
				satisfied[i] = false;
				for (size_t j = 0; j <= i; j++) {
					if (denominations.find(j) == denominations.end() && reachable[i - j]) {
						possible[i].insert(j);
					}
				}
			}
		}
		u32 needed = 0;
		while (!allTrue(satisfied)) {
			u32 max = 0;
			u32 maxValue = v + 1;
			for (u32 i = 0; i <= v; i++) {
				u32 count = 0;
				for (map<u32, set<u32> >::iterator iter = possible.begin(); iter != possible.end(); iter++) {
					if ((iter->second).find(i) != (iter->second).end() && !satisfied[iter->first]) {
						count++;
					}
				}
				if (count > max) {
					max = count;
					maxValue = i;
				}
			}
			for (map<u32, set<u32> >::iterator iter = possible.begin(); iter != possible.end(); iter++) {
				if (!satisfied[iter->first] && possible[iter->first].find(maxValue) != possible[iter->first].end()) {
					satisfied[iter->first] = true;
				}
			}
			needed++;
		}
		cout << "Case #" << t << ": " << needed << '\n';
	}
	return 0;
}