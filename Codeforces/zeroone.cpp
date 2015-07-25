#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
	int n;
	string s;
	cin >> n >> s;
	int num0 = 0, num1 = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s.at(i) == '0') {
			num0++;
		} else {
			num1++;
		}
	}
	cout << (max(num0, num1) - min(num0, num1)) << '\n';
	return 0;
}