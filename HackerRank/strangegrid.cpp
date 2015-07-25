#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	unsigned long r, c;
	cin >> r >> c;
	r--;
	c--;
	cout << (r / 2) * 10 + (r % 2) + (c * 2);
	return 0;
}