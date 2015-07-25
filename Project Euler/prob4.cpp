#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#define SSTR(x) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

bool isPalindrome(string s) {
	for (int i = 0; i < (s.size() >> 1); i++) {
		if (s.at(i) != s.at(s.size() - i - 1)) {
			return false;
		}
	}
	return true;
}

int main() {
	int largest = 0;
	for (int i = 100; i <= 999; i++) {
		for (int j = 100; j <= 999; j++) {
			if (isPalindrome(SSTR(i * j)) && i * j > largest) {
				largest = i * j;
			}
		}
	}
	cout << largest << '\n';
}