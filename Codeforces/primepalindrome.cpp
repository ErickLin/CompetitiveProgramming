#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int main() {
    int p, q;
    cin >> p >> q;
    int n = 1179858;
    vector<bool> isPrime(n + 1);
    for (int i = 2; i <= n; i++) {
        isPrime[i] = true;
    }
    for (int i = 2; i <= (int) sqrt(n); i++) {
        for (int j = i * i; j <= n; j += i) {
            isPrime[j] = false;
        }
    }
    vector<int> numPrimes(n + 1);
    for (int i = 1; i <= n; i++) {
        numPrimes[i] = numPrimes[i - 1];
        if (isPrime[i]) {
            numPrimes[i]++;
        }
    }
    vector<int> numPalLen(7);
    numPalLen[1] = 9;
    numPalLen[2] = 9;
    for (int i = 3; i <= 6; i++) {
        if (i % 2 == 1) {
            numPalLen[i] = 10 * numPalLen[i - 1];
        } else {
            numPalLen[i] = 10 * numPalLen[i - 2];
        }
    }
    int max = -1;
    int palCount = 0;
    /*
    int len = 0;
    int cmp = 1;
    while (q * numPrimes[cmp] <= p * palCount && cmp <= 1000000) {
        palCount += numPalLen[len];
        len++;
        cmp *= 10;
    }
    cout << palCount << '\n';
    */
    for (int j = 1; j <= n; j++) {
        ostringstream convert;
        convert << j;
        string s = convert.str();
        string t = s;
        reverse(t.begin(), t.end());
        if (s == t) {
            palCount++;
        }
        if (q * numPrimes[j] <= p * palCount) {
            max = j;
        }
    }
    cout << max << '\n';
    return 0;
}
