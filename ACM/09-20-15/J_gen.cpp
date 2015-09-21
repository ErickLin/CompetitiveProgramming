#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    cout << "1000\n";
    for (int i = 0; i < 1000; i++) {
        cout << -1000 + (rand() % 2001) << ' ' << -1000 + (rand() % 1001) << '\n';
    }
    cout << "0\n";
    return 0;
}
