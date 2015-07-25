#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	long long a = 600851475143;
	int b = (int) sqrt(a);
	vector<bool> isPrime(b + 2);
	fill(isPrime.begin(), isPrime.end(), true);
	isPrime[0] = false;
	isPrime[1] = false;
	for (int i = 2; i <= sqrt(b) + 1; i++) {
		if (isPrime[i]) {
			for (int j = i * i; j <= b + 1; j += i) {
				isPrime[j] = false;
			}
		}
	}
	for (int i = b + 1; i >= 0; i--) {
		if (isPrime[i] && a % (long) i == 0) {
			cout << i << '\n';
			return 0;
		}
	}
}