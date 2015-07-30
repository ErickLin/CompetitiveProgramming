/*
ID: Jugglebrosjr2
LANG: C++
TASK: bigbrn
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    ifstream fin("bigbrn.in");
    ofstream fout("bigbrn.out");
    int n, t;
    fin >> n >> t;
    vector<vector<bool> > hasTree(n, vector<bool>(n));
    for (int i = 0; i < t; i++) {
        int r, c;
        fin >> r >> c;
        hasTree[--r][--c] = true;
    }
    int max = 0;
    int lo = 1, hi = n;
    while (lo <= hi) {
        int mid = lo + ((hi - lo) >> 1);
        bool found = false;
        for (int i = 0; i + mid <= n && !found; i++) {
            for (int j = 0; j + mid <= n && !found; j++) {
                bool valid = true;
                for (int r = i; r < i + mid && valid; r++) {
                    for (int c = j; c < j + mid && valid; c++) {
                        if (hasTree[r][c]) {
                            valid = false;
                        }
                    }
                }
                if (valid) {
                    found = true;
                    max = mid;
                    lo = mid + 1;
                }
            }
        }
        if (!found) {
            hi = mid - 1;
        }
    }
    fout << max << '\n';
    return 0;
}
