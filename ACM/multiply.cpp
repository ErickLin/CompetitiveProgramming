#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	string a, b;
	cin >> a;
	cin >> b;
	vector<int> n1(a.size());
	for (unsigned i = 0; i < a.length(); i++) {
		n1[i] = a[i] - '0';
	}
	vector<int> n2(b.size());
	for (unsigned i = 0; i < b.length(); i++) {
		n2[i] = b[i] - '0';
	}
	for (int t = 1; n1[0] != 0; t++) {
		vector<vector<vector<int> > > table(
				b.size(), vector<vector<int> >(a.size(),
				vector<int>(2)));
		for (unsigned i = 0; i < b.size(); i++) {
			for (unsigned j = 0; j < a.size(); j++) {
				table[i][j][0] = n2[i] * n1[j] / 10;
				table[i][j][1] = n2[i] * n1[j] % 10;
			}
		}
		vector<int> ans(a.size() + b.size());
		int carry = 0;
		for (int diagNum = a.size() + b.size() - 1;
				diagNum >= 0; diagNum--) {
			ans[diagNum] += carry;
			carry = 0;
			for (int z = 0; z <= 1; z++) {
				for (int y = 0; y < a.size(); y++) {
					int x = diagNum - y - z;
					if (x < 0 || x >= b.size()) {
						continue;
					}
					ans[diagNum] += table[x][y][z];
					if (ans[diagNum] >= 10) {
						ans[diagNum] -= 10;
						carry += 1;
					}
				}
			}
		}
		/*
		for (int i = 0; i < b.size(); i++) {
			for (int j = 0; j < a.size(); j++) {
				cout << table[i][j][0] << " " << table[i][j][1] << "  ";
			}
			cout << '\n';
		}
		*/
		int r = b.size() + 3 * (b.size() + 1) + 2;
		int c = a.size() + 3 * (a.size() + 1) + 2;
		bool zero = true;

		cout << '+';
		for (int j = 1; j < c - 1; j++) {
			cout << '-';
		}
		cout << '+' << '\n';

		//print out n1
		cout << "|   ";
		for (int j = 0; j < a.size(); j++) {
			cout << n1[j] << "   ";
		}
		cout << '|' << '\n';

		//print out table
		for (int i = 0; i < b.size(); i++) {
			//top border
			cout << "| ";
			for (int j = 0; j < a.size(); j++) {
				cout << "+---";
			}
			cout << "+ |\n";
			//row 1/3
			cout << '|';
			if (i > 0 && !zero) {
				cout << '/';
			} else {
				cout << ' ';
			}
			for (int j = 0; j < a.size(); j++) {
				cout << '|' << table[i][j][0] << " /";
			}
			cout << "| |\n";
			//row 2/3
			cout << "| |";
			for (int j = 0; j < a.size(); j++) {
				cout << " / |";
			}
			cout << n2[i] << "|\n";
			//row 3/3
			cout << '|';
			if (ans[i] > 0 || !zero) {
				cout << ans[i];
				zero = false;
			} else {
				cout << ' ';
			}
			for (int j = 0; j < a.size(); j++) {
				cout << "|/ " << table[i][j][1];
			}
			cout << "| |\n";
		}

		cout << "| ";
		for (int j = 0; j < a.size(); j++) {
			cout << "+---";
		}
		cout << "+ |\n";

		cout << '|';
		for (int j = b.size(); j < ans.size(); j++) {
			if (zero) {
				cout << ' ';
			} else {
				cout << '/';
			}
			cout << ' ' << ans[j] << ' ';
			if (ans[j] > 0)
				zero = false;
		}
		cout << "   |\n";

		cout << '+';
		for (int j = 1; j < c - 1; j++) {
			cout << '-';
		}
		cout << '+' << '\n';

		cin >> a;
		cin >> b;
		n1.clear();
		n1.resize(a.size());
		for (unsigned i = 0; i < a.length(); i++) {
			n1[i] = a[i] - '0';
		}
		n2.clear();
		n2.resize(b.size());
		for (unsigned i = 0; i < b.length(); i++) {
			n2[i] = b[i] - '0';
		}
	}
}