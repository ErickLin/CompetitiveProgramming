#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	unsigned int t;
	cin >> t;
	for (unsigned int i = 0; i < t; i++) {
		string str;
		cin >> str;
		vector<char> s(str.size());
		vector<char> r(str.size());
		for (int i = 0; i < str.size(); i++) {
			s[i] = str.at(i);
			r[i] = str.at(str.size() - i - 1);
		}
		bool funny = true;
		for (int i = 1; i < s.size() && funny; i++) {
			if (abs(s[i] - s[i - 1]) != abs(r[i] - r[i - 1])) {
				cout << "Not Funny\n";
				funny = false;
			}
		}
		if (funny) {
			cout << "Funny\n";
		}
	}
}