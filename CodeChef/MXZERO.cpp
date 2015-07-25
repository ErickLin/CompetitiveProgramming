#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main(int argc, char** argv) {
	u32 T;
	cin >> T;
	for (u32 t = 0; t < T; t++) {
		u32 n, n1 = 0, n0 = 0;
		cin >> n;
		vector<u32> a(n);
		for (u32 i = 0; i < n; i++) {
			cin >> a[i];
			if (a[i] == 1)
				n1++;
			else
				n0++;
		}
		if (n1 % 2 == 0) {
			cout << n0;
		} else {
			cout << n1;
		}
		cout << '\n';
	}
	return 0;
}