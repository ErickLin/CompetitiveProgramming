// 515B
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	unsigned int n, m, b, g;
	cin >> n >> m;
	vector<bool> isHappy(max(n, m));
	set<int> happy;
	cin >> b;
	for (unsigned int i = 0; i < b; i++) {
		unsigned int h;
		cin >> h;
		isHappy[h] = true;
		happy.insert(h);
	}
	cin >> g;
	for (unsigned int i = 0; i < g; i++) {
		unsigned int h;
		cin >> h;
		isHappy[h] = true;
		happy.insert(h);
	}
	for (set<int>::iterator itr = happy.begin(); itr != happy.end(); itr++) {
		int c = *itr;
		for (int i = 0; i < max(n, m); i++) {
			c += min(n, m);
			if (c >= max(n, m)) {
				c %= max(n, m);
			}
			isHappy[c] = true;
		}
	}
	bool allHappy = true;
	for (int i = 0; i < max(n, m); i++) {
		if (!isHappy[i]) {
			allHappy = false;
			cout << "No\n";
			break;
		}
	}
	if (allHappy) {
		cout << "Yes\n";
	}
	return 0;
}
