#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int compare(vector<char> str1, vector<char> str2) {
	for (int pos = 0; pos < min(str1.size(), str2.size()); pos++) {
		if (str1[pos] < str2[pos]) {
			return -1;
		} else if (str1[pos] > str2[pos]) {
			return 1;
		}
	}
	if (str1.size() < str2.size()) {
		return -1;
	} else if (str1.size() > str2.size()) {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		string temp;
		cin >> temp;
		vector<char> str(n);
		for (int pos = 0; pos < n; pos++) {
			str[pos] = temp.at(pos);
		}
		vector<char> min(n);
		min = str;
		for (int pos = 0; pos < n; pos++) {
			vector<char> newStr(n);
			newStr = str;
			for (int newPos = pos + 1; newPos < n; newPos++) {
				char temp = newStr[newPos - 1];
				newStr[newPos - 1] = newStr[newPos];
				newStr[newPos] = temp;
				if (compare(newStr, min) < 0) {
					min = newStr;
				}
			}
			newStr = str;
			for (int newPos = pos - 1; newPos >= 0; newPos--) {
				char temp = newStr[newPos + 1];
				newStr[newPos + 1] = newStr[newPos];
				newStr[newPos] = temp;
				if (compare(newStr, min) < 0) {
					min = newStr;
				}
			}
		}
		for (int pos = 0; pos < n; pos++) {
			cout << min[pos];
		}
		cout << '\n';
	}
	return 0;
}