#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
	if (max(a, b) % min(a, b) == 0) {
		return min(a, b);
	} else {
		return gcd(max(a, b) % min(a, b), min(a, b));
	}
}

long long lcm(long long a, long long b) {
	return a * b / gcd(a, b);
}

int main() {
	long long pre = lcm(1, 2);
	for (int i = 3; i <= 20; i++) {
		pre = lcm(pre, i);
	}
	cout << pre << '\n';
}