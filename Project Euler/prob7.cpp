#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    vector<bool> isPrime(900001);
    for (int i = 2; i <= 900000; i++) {
        isPrime[i] = true;
    }
    int count = 0;
    for (int i = 2; i + i <= 900000; i++) {
        if (isPrime[i]) {
            if (++count == 10001) {
                cout << i << '\n';
                return 0;
            }
            cout << count << ' ' << i << '\n';
            for (int j = i + i; j <= 900000; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return 0;
}
