#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
unsigned int p = 97;
unsigned long q = 10000019;

bool exists(unsigned long len) {
	for (int i = 0;)
}

int main() {
	ios_base::sync_with_stdio(false);
	unsigned int n, k;
	cin >> n >> k;
	vector<unsigned long> q(n);
	for (int i = 0; i < n; i++) {
		cin >> q[i];
	}
	unsigned long len = n / 2;
	while (len <= n - 1) {
		vector<unsigned int> h(60000);
		unsigned long long hash = q[0];
		for (int i = 1; i < n - len; i++) {
			unsigned long long hash = ((hash * 97) % q + c[i]) % q;
		}
	}
	return 0;
}