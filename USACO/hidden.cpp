/*
ID: Jugglebrosjr2
LANG: C++
TASK: hidden
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    ifstream fin("hidden.in");
    ofstream fout("hidden.out");
    int n;
    fin >> n;
    vector<char> s(n);
    for (int i = 0; i < n; i++) {
        fin >> s[i];
    }
    int i = 0, j = 1, k = 0;
    while (j < n && k < n) {
        k = 0;
        while (k < n && s[(i + k) % n] == s[(j + k) % n]) {
            k++;
        }
        if (k < n) {
            if (s[(i + k) % n] > s[(j + k) % n]) {
                i += k + 1;
            } else {
                j += k + 1;
            }
            if (i == j) {
                j++;
            }
        }
    }
    fout << i << '\n';
    return 0;
}
