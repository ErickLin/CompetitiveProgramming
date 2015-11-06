#include <cstdlib>
#include <iostream>
using namespace std;
int C = -1000000000;

int main() {
    cout << "100000 100000\n";
    for (int i = 0; i < 100000; i++) {
        cout << C + rand() << ' ' << C + rand() << '\n';
    }
    for (int i = 0; i < 100000; i++) {
        if (rand() % 2 == 0) {
            cout << "x:";
        } else {
            cout << "y:";
        }
        cout << C + rand() << '\n';
    }
    cout << "0 0\n";
}
