#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n, k, p;
		cin >> n >> k >> p;
		vector<int> a;
		int pSmallest = p;
		for (int j = 0; j < k; j++) {
			int b;
			cin >> b;
			if (b <= pSmallest) {
				pSmallest++;
			}
		}
		if (pSmallest > n) {
			pSmallest = -1;
		}
		cout << pSmallest << endl;
	}
	return 0;
}