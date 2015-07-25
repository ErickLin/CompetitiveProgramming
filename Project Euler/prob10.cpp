#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long sum = 0;
    vector<bool> isPrime(2000000);
    for (int i = 2; i < 2000000; i++) {
        isPrime[i] = true;
    }
    for (int i = 2; i < 2000000; i++) {
        if (isPrime[i]) {
            sum += i;
            for (long long j = (long long) i * i; j < 2000000; j += i) {
                isPrime[j] = false;
            }
        }
    }
    cout << sum << '\n';
}
