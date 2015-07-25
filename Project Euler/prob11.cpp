#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int> > a(20, vector<int>(20));
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cin >> a[i][j];
        }
    }
    int maxProd = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (j + 3 < 20) {
                int prod = 1;
                for (int k = 0; k < 4; k++) {
                    prod *= a[i][j + k];
                }
                if (prod > maxProd) {
                    maxProd = prod;
                }
            }
            if (i + 3 < 20) {
                int prod = 1;
                for (int k = 0; k < 4; k++) {
                    prod *= a[i + k][j];
                }
                if (prod > maxProd) {
                    maxProd = prod;
                }
            }
            if (i + 3 < 20 && j + 3 < 20) {
                int prod = 1;
                for (int k = 0; k < 4; k++) {
                    prod *= a[i + k][j + k];
                }
                if (prod > maxProd) {
                    maxProd = prod;
                }
            }
            if (i + 3 < 20 && j - 3 >= 0) {
                int prod = 1;
                for (int k = 0; k < 4; k++) {
                    prod *= a[i + k][j - k];
                }
                if (prod > maxProd) {
                    maxProd = prod;
                }
            }
        }
    }
    cout << maxProd << '\n';
}
