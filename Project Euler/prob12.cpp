#include <cmath>
#include <iostream>
using namespace std;

int main() {
    long long num = 1;
    for (long long d = 2; ; d++) {
        int count = 0;
        for (long long i = 1; i <= sqrt(num); i++) {
            if (num % i == 0) {
                count++;
                if (count > 250) {
                    cout << num << '\n';
                    return 0;
                }
            }
        }
        //cout << num << ' ' << count << '\n';
        num += d;
    }
    return 0;
}
