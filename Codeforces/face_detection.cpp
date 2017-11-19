// 549A
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <cmath>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
	u32 n, m;
	cin >> n >> m;
	vector<vector<char> > pic(n, vector<char>(m));
	u32 count = 0;
	for (u32 i = 0; i < n; i++) {
		for (u32 j = 0; j < m; j++) {
			cin >> pic[i][j];
		}
	}
	for (u32 i = 0; i < n - 1; i++) {
		for (u32 j = 0; j < m - 1; j++) {
			set<char> sq;
			sq.insert(pic[i][j]);
			sq.insert(pic[i + 1][j]);
			sq.insert(pic[i][j + 1]);
			sq.insert(pic[i + 1][j + 1]);
			if (sq.find('f') != sq.end()
					&& sq.find('a') != sq.end()
					&& sq.find('c') != sq.end()
					&& sq.find('e') != sq.end()) {
				count++;
			}
		}
	}
	cout << count << '\n';
	return 0;
}
