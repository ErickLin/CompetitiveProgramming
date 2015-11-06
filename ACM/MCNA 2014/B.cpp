#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	int w;
	cin >> w;
	int l;
	cin >> l;
	for (int t = 1; w != 0; t++) {
		vector< vector<char> > house(l, vector<char>(w));
		pair<int, int> start;
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < w; j++) {
				cin >> house[i][j];
				if (house[i][j] == '*')
					start = make_pair(i, j);
			}
		}
		pair<int, int> loc = make_pair(start.first, start.second);
		int E = 0;
		int S = 1;
		int W = 2;
		int N = 3;
		int dir;
		if (loc.first == 0) {
			dir = S;
		} else if (loc.second == 0) {
			dir = E;
		} else if (loc.first == w - 1) {
			dir = N;
		} else {
			dir = W;
		}
		do {
			if (dir == S) {
				loc.first++;
			int i = loc.first;
			int j = loc.second;
				if (house[i][j] == '/') {
					dir = W;
				} else if (house[i][j] == '\\') {
					dir = E;
				}
			} else if (dir == E) {
				loc.second++;
			int i = loc.first;
			int j = loc.second;
				if (house[i][j] == '/') {
					dir = N;
				} else if (house[i][j] == '\\') {
					dir = S;
				}
			} else if (dir == N) {
				loc.first--;
			int i = loc.first;
			int j = loc.second;
				if (house[i][j] == '/') {
					dir = E;
				} else if (house[i][j] == '\\') {
					dir = W;
				}
			} else if (dir == W) {
				loc.second--;
			int i = loc.first;
			int j = loc.second;
				if (house[i][j] == '/') {
					dir = S;
				} else if (house[i][j] == '\\') {
					dir = N;
				}
			}
		} while (loc.first != 0 && loc.second != 0
				&& loc.first != l - 1 && loc.second != w - 1);
		house[loc.first][loc.second] = '&';
		cout << "HOUSE " << t << '\n';
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < w; j++) {
				cout << house[i][j];
			}
			cout << '\n';
		}
		cin >> w;
		cin >> l;
	}
	return 0;
}