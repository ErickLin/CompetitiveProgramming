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

void print(vector<vector<char> >& pict) {
	u32 n = pict.size();
	for (u32 i = 0; i < n; i++) {
		for (u32 j = 0; j < n; j++) {
			cout << noskipws << pict[i][j];
		}
		cout << '\n';
	}
	cout << '\n';
}

bool layerMatch(vector<vector<char> >& p1, vector<vector<char> >& p2, u32 layer) {
	u32 n = p1.size();
	for (u32 i = layer; i < n - layer; i++) {
		if (p1[i][layer] != p2[i][layer] || p1[i][n - layer - 1] != p2[i][n - layer - 1]
				|| p1[layer][i] != p2[layer][i] || p1[n - layer - 1][i] != p2[n - layer - 1][i]) {
			return false;
		}
	}
	return true;
}

void rotate(vector<vector<char> >& pict, u32 layer) {
	u32 n = pict.size();
	for (u32 i = layer; i < n - layer - 1; i++) {
		char temp = pict[i][n - layer - 1];
		pict[i][n - layer - 1] = pict[layer][i];

		char temp2 = pict[n - layer - 1][n - 1 - i];
		pict[n - layer - 1][n - 1 - i] = temp;

		temp = pict[n - 1 - i][layer];
		pict[n - 1 - i][layer] = temp2;

		pict[layer][i] = temp;
	}
}

int main() {
	string line;
	getline(cin, line);
	u32 n = line.at(0) - '0';
	vector<vector<char> > p1(n, vector<char>(n)), p2(n, vector<char>(n));
	for (u32 i = 0; i < n; i++) {
		getline(cin, line);
		for (u32 j = 0; j < n; j++) {
			p1[i][j] = line.at(j);
		}
	}
	for (u32 i = 0; i < n; i++) {
		getline(cin, line);
		for (u32 j = 0; j < n; j++) {
			p2[i][j] = line.at(j);
		}
	}
	bool matching = true;
	for (u32 layer = 0; layer < ((n + 1) >> 1) && matching; layer++) {
		for (u32 i = 0; i < 4 && !layerMatch(p1, p2, layer); i++) {
			matching = false;
			rotate(p2, layer);
			if (layerMatch(p1, p2, layer)) {
				matching = true;
			}
		}
	}
	if (matching/* && ((n & (1 << 0)) == 0 || p1[n >> 1] == p2[n >> 1])*/) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
	return 0;
}