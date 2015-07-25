#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Hexspeak {
    public:
        string decode(long long ciphertext) {
        	bool error = false;
        	string ans = "";
            for (int i = 0; i < 16 && !error && ciphertext > 0; i++) {
            	if (ciphertext % 16 == 0) {
            		ans = 'O' + ans;
            	} else if (ciphertext % 16 == 1) {
            		ans = 'I' + ans;
            	} else if (ciphertext % 16 >= 10 && ciphertext % 16 <= 15) {
            		ans = (char) ('A' + (ciphertext % 16 - 10)) + ans;
            	} else {
            		ans = "Error!";
            		error = true;
            	}
            	ciphertext /= 16;
            }
            if (error) {
            	return "Error!";
            } else {
            	return ans;
            }
        }
};

int main() {
	Hexspeak a;
	cout << a.decode(257) << '\n';
	cout << a.decode(258) << '\n';
	cout << a.decode(2573405691582) << '\n';
	cout << a.decode(2882400001) << '\n';
	cout << a.decode(999994830345994239) << '\n';
	cout << a.decode(1000000000000000000) << '\n';
}