#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

bool isQuasigroup(vector<vector<long long> > m) {
	int n = m.size();
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int zCount = 0;
			int wCount = 0;
			for (int u = 0; u < n; u++) {
				if (m[x][u] == y) {
					zCount++;
				}
				if (m[u][x] == y) {
					wCount++;
				}
			}
			if (zCount != 1 || wCount != 1) {
				return false;
			}
		}
	}
	return true;
}

bool isLoop(vector<vector<long long> > m) {
	int n = m.size();
	int eCount = 0;
	for (int e = 0; e < n; e++) {
		bool isE = true;
		for (int x = 0; x < n; x++) {
			if (m[e][x] != x || m[x][e] != x) {
				isE = false;
			}
		}
		if (isE) {
			eCount++;
		}
	}
	if (eCount == 1) {
		return true;
	} else {
		return false;
	}
}

bool isSemigroup(vector<vector<long long> > m) {
	int n = m.size();
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int z = 0; z < n; z++) {
				if (m[x][y] >= n || m[y][z] >= n
						|| m[m[x][y]][z] != m[x][m[y][z]]) {
					return false;
				}
			}
		}
	}
	return true;
}

bool isMonoid(vector<vector<long long> > m) {
	return isLoop(m);
}

bool isGroup(vector<vector<long long> > m) {
	int n = m.size();
	int e;
	for (e = 0; e < n; e++) {
		bool isE = true;
		for (int x = 0; x < n; x++) {
			if (m[e][x] != x || m[x][e] != x) {
				isE = false;
			}
		}
		if (isE) {
			break;
		}
	}
	for (int x = 0; x < n; x++) {
		bool hasY = false;
		for (int y = 0; y < n && !hasY; y++) {
			bool isY = true;
			if (m[x][y] != e || m[y][x] != e) {
				isY = false;
			}
			if (isY) {
				hasY = true;
			}
		}
		if (!hasY) {
			return false;
		}
	}
	return true;
}

bool isAbelianGroup(vector<vector<long long> > m) {
	int n = m.size();
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (m[x][y] != m[y][x]) {
				return false;
			}
		}
	}
	return true;
}

bool isRack(vector<vector<long long> > m) {
	int n = m.size();
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int zCount = 0;
			for (int z = 0; z < n; z++) {
				if (m[x][z] == y) {
					zCount++;
				}
			}
			if (zCount != 1) {
				return false;
			}
		}
	}
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int z = 0; z < n; z++) {
				if (m[y][z] >= n || m[x][y] >= n || m[x][z] >= n
						|| m[x][m[y][z]] != m[m[x][y]][m[x][z]]) {
					return false;
				}
			}
		}
	}
	return true;
}

bool isQuandle(vector<vector<long long> > m) {
	int n = m.size();
	for (int x = 0; x < n; x++) {
		if (m[x][x] != x) {
			return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int k = 0; k < t; k++) {
		int n;
		cin >> n;
		vector<vector<long long> > magma(n, vector<long long>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> magma[i][j];
			}
		}
		int s = 0;
		if (isQuasigroup(magma)) {
			s++;
			if (isLoop(magma)) {
				s += 2;
			}
		}
		if (isSemigroup(magma)) {
			s += 4;
			if (isMonoid(magma)) {
				s += 8;
				if (isGroup(magma)) {
					s += 16;
					if (isAbelianGroup(magma)) {
						s += 32;
					}
				}
			}
		}
		if (isRack(magma)) {
			s += 64;
			if (isQuandle(magma)) {
				s += 128;
			}
		}
		cout << s << '\n';
	}
	return 0;
}