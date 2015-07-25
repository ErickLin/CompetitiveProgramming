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

u32 numW(string x, u32 yLen) {
	u32 ret = 0;
	u32 n = x.length();
	bool can = true;
	for (u32 pos = 0; pos < yLen && can; pos++) {
		if (x.at(n - pos - 1) != x.at(n - pos - 1 - yLen)) {
			can = false;
		}
	}
	if (can) ret++;

	can = true;
	for (u32 pos = 0; pos < yLen && can; pos++) {
		if (x.at(n - pos - 1) != x.at(yLen - pos - 1)) {
			can = false;
		}
	}
	if (can) ret++;

	can = true;
	for (u32 pos = 0; pos < yLen && can; pos++) {
		if (x.at(n - pos - 1 - yLen) != x.at(yLen - pos - 1)) {
			can = false;
		}
	}
	if (can) ret++;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	string x;
	cin >> x;
	u32 count = 0;
	for (u32 wLen = ((x.length() & (1 << 0)) == 0 ? 2 : 1); wLen < x.length(); wLen += 2) {
		count += numW(x, (x.length() - wLen) >> 1);
	}
	cout << count << '\n';
	return 0;
}