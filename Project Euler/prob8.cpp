#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    vector<char> a(1000);
    for (int i = 0; i < 1000; i++) {
        cin >> a[i];
        a[i] -= '0';
    }
    long long ans = 0;
    for (int i = 0; i <= 987; i++) {
        long long prod = 1;
        for (int j = 0; j < 13; j++) {
            prod *= a[i + j];
        }
        if (prod > ans) {
            ans = prod;
        }
    }
    cout << ans << '\n';
}
