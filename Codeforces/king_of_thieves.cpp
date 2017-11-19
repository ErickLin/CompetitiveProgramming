// 526A
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	u32 n;
	cin >> n;
	vector<char> level(n);
	for (u32 i = 0; i < n; i++) {
		cin >> level[i];
	}
	bool found = false;
	for (u32 jumpLen = 1; jumpLen < n && !found; jumpLen++) {
		for (u32 start = 0; start < jumpLen && !found; start++) {
			u32 streak = 0;
			for (u32 pos = start; pos < n && !found; pos += jumpLen) {
				if (level[pos] == '*') {
					if (++streak >= 5) {
						found = true;
					}
				} else {
					streak = 0;
				}
			}
		}
	}
	if (found) {
		cout << "yes\n";
	} else {
		cout << "no\n";
	}
	return 0;
}
