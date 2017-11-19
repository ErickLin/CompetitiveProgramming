// 514A
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	string str;
	getline(cin, str);
	vector<unsigned char> num(str.begin(), str.end());
	if (num[0] >= '5' && num[0] < '9') {
		num[0] = '9' - num[0] + 48;
	}
	cout << num[0];
	for (int i = 1; i < num.size(); i++) {
		if (num[i] >= '5') {
			num[i] = '9' - num[i] + 48;
		}
		cout << num[i];
	}
	cout << endl;
	return 0;
}
