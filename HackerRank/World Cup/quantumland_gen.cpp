#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 100000;
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int next = rand() % n;
        while (next == i) {
            next = rand() % n;
        }
        int prob = rand() % (101);
        cout << (next + 1) << " " << prob << '\n';
    }
}
