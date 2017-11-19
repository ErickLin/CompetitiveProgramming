// 554A
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
	string s;
	cin >> s;
	cout << 26 * (s.length() + 1) - s.length() << '\n';
	return 0;
}
