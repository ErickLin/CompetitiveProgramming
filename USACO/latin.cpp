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

long long fill(int r, int c, vector<vector<vector<bool> > > &choices) {
    int n = choices.size();
    //first n - 1 lines automatically determine last line
    if (r == n - 1) {
        /*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << sq[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
        */
        return 1;
    }
    long long res = 0;
    for (int k = 1; k < choices[r][c].size(); k++) {
        if (choices[r][c][k]) {
            //sq[r][c] = *it;
            vector<bool> erasedRow(n), erasedCol(n);
            for (int i = r + 1; i < n; i++) {
                if (choices[i][c][k]) {
                    choices[i][c][k] = false;
                    erasedRow[i] = true;
                }
            }
            for (int j = c + 1; j < n; j++) {
                if (choices[r][j][k]) {
                    choices[r][j][k] = false;
                    erasedCol[j] = true;
                }
            }
            long long dRes = fill(c == n - 1 ? r + 1 : r, c == n - 1 ? 1 : c + 1, choices);
            //sq[r][c] = 0;
            for (int i = r + 1; i < n; i++) {
                if (erasedRow[i]) {
                    choices[i][c][k] = true;
                }
            }
            for (int j = c + 1; j < n; j++) {
                if (erasedCol[j]) {
                    choices[r][j][k] = true;
                }
            }
            if (r == 1 && k > c + 1) {
                res += (n - k + 1) * dRes;
                break;
            } else {
                res += dRes;
            }
        }
    }
    return res;
}

int main() {
    ifstream fin("latin.in");
    ofstream fout("latin.out");
    int n;
    fin >> n;
    //vector<vector<int> > sq(n, vector<int>(n));
    vector<vector<vector<bool> > > choices(n, vector<vector<bool> >(n, vector<bool>(n + 1)));
    /*
    for (int i = 0; i < n; i++) {
        sq[0][i] = i + 1;
        sq[i][0] = i + 1;
    }
    */
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            for (int k = 1; k <= n; k++) {
                if (k != i + 1 && k != j + 1) {
                    choices[i][j][k] = true;
                }
            }
        }
    }
    long long fac = 1;
    for (int i = 2; i < n; i++) {
        fac *= i;
    }
    fout << fac * fill(1, 1, choices) << '\n';
    return 0;
}
