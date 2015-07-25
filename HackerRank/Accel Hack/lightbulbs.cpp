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
	ios_base::sync_with_stdio(false);
	/*
	set<u32> squares;
	for (u32 c = 1; c * c <= 1000000000; c++) {
		squares.insert(c * c);
	}
	vector<u32> lastSquare(1000000001);
	for (u32 i = 1; i <= 1000000000; i++) {
		if (squares.find(i) != squares.end()) {
			lastSquare[i] = i;
		} else {
			lastSquare[i] = lastSquare[i - 1];
		}
	}
	*/
	u32 t;
	cin >> t;
	while (t--) {
		u32 n;
		cin >> n;
		cout << (int) (sqrt(n)) << '\n';
	}
	return 0;
}