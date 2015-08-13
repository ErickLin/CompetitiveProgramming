/*
ID: Jugglebrosjr2
LANG: C++
TASK: latin
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

vector<bool> temp;

long long fill(int r, int c, vector<bool> &usedRow, vector<vector<bool> > &usedCol) {
    int n = usedCol.size();
    //first n - 1 lines automatically determine last line
    if (r == n - 1) {
        return 1;
    }
    if (c == 1) {
        temp = usedRow;
        fill(usedRow.begin(), usedRow.end(), 0);
        usedRow[r + 1] = true;
    }
    long long res = 0;
    for (int k = 1; k <= n; k++) {
        if (!usedRow[k] && !usedCol[c][k]) {
            usedRow[k] = true;
            usedCol[c][k] = true;
            long long dRes = fill(c == n - 1 ? r + 1 : r, c == n - 1 ? 1 : c + 1
                    , usedRow, usedCol);
            usedRow[k] = false;
            usedCol[c][k] = false;
            if (r == 1 && k > c + 1) {
                res += (n - k + 1) * dRes;
                break;
            } else {
                res += dRes;
            }
        }
    }
    if (c == 1) {
        usedRow = temp;
    }
    return res;
}

int main() {
    ifstream fin("latin.in");
    ofstream fout("latin.out");
    int n;
    fin >> n;
    //keep track of which numbers have been used in each row and column
    vector<bool> usedRow(n + 1);
    vector<vector<bool> > usedCol(n, vector<bool>(n + 1));
    for (int j = 0; j < n; j++) {
        usedCol[j][j + 1] = true;
    }
    long long fac = 1;
    for (int i = 2; i < n; i++) {
        fac *= i;
    }
    fout << fac * fill(1, 1, usedRow, usedCol) << '\n';
    return 0;
}
