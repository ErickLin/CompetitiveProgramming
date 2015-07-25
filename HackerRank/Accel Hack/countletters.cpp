#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int u32;

map<char, u32> occs;

bool cmp(char a, char b) {
	if (occs[a] == occs[b]) {
		return a < b;
	} else {
		return occs[a] > occs[b];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	u32 t;
	cin >> t;
	while (t--) {
		occs.clear();
		u32 n, k;
		cin >> n >> k;
		string s;
		cin >> s;
		vector<char> arr;
		for (u32 i = 0; i < s.length(); i++) {
			occs[s.at(i)]++;
		}
		for (map<char, u32>::iterator it = occs.begin(); it != occs.end(); it++) {
			//cout << it->first << ' ' << it->second << '\n';
			if (it->second > k) {
				arr.push_back(it->first);
			}
		}
		sort(arr.begin(), arr.end(), cmp);
		if (arr.empty()) {
			cout << "NONE";
		} else {
			for (u32 i = 0; i < arr.size(); i++) {
				cout << arr[i];
			}
		}
		cout << '\n';
	}
	return 0;
}