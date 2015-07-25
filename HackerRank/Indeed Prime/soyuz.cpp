#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
	u32 n;
	cin >> n;
	cout << "  /\\\n";
	for (u32 i = 0; i < n; i++) {
		cout << "  ||\n";
	}
	cout << " /||\\\n";
	cout << "/:||:\\\n";
	for (u32 i = 0; i < n - 1; i++) {
		cout << "|:||:|\n";
	}
	cout << "|/||\\|\n";
	cout << "  **\n  **\n";
	return 0;
}