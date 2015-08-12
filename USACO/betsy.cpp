/*
ID: Jugglebrosjr2
LANG: C++
TASK: betsy
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

long long gen(int i, int j, long long vis, vector<int> &visRow
        , vector<int> &visCol, vector<vector<int> > &neighborsVis, int n) {
    if (i == 0 && j == 0 && vis == (1ULL << (n * n)) - 1) {
        return 1;
    }
    long long locBitUp = 1ULL << ((i - 1) * n + j)
        , locBitDown = 1ULL << ((i + 1) * n + j)
        , locBitLeft = 1ULL << (i * n + (j - 1))
        , locBitRight = 1ULL << (i * n + (j + 1));
    if (i > 0 && visRow[i - 1] == n) {
        return 0;
    }
    if (j > 0 && visCol[j - 1] == n) {
        return 0;
    }
    if ((vis & locBitUp) && (vis & locBitDown) && !(vis & locBitLeft)
            && !(vis & locBitRight)) {
        return 0;
    }
    if ((vis & locBitLeft) && (vis & locBitRight) && !(vis & locBitUp)
            && !(vis & locBitDown)) {
        return 0;
    }
    if (i == 0 && j < n - 1 && !(vis & locBitRight)) {
        return 0;
    }
    if (j == 0 && i < n - 1 && !(vis & locBitDown)) {
        return 0;
    }
    if (i == n - 1 && j > 0 && !(vis & locBitLeft)) {
        return 0;
    }
    if (j == n - 1 && i < n - 1 && !(vis & locBitDown)) {
        return 0;
    }
    long long res = 0;
    bool canUp = true, canDown = true, canLeft = true, canRight = true;
    bool canUp2 = false, canDown2 = false, canLeft2 = false, canRight2 = false;
    if (i > 0) {
        neighborsVis[i - 1][j]++;
        if (!(vis & locBitUp) && neighborsVis[i - 1][j] >= 3) {
            canDown = false;
            canLeft = false;
            canRight = false;
        }
    }
    if (i < n - 1) {
        neighborsVis[i + 1][j]++;
        if (!(vis & locBitDown) && neighborsVis[i + 1][j] >= 3) {
            canUp = false;
            canLeft = false;
            canRight = false;
        }
    }
    if (j > 0) {
        neighborsVis[i][j - 1]++;
        if (!(vis & locBitLeft) && neighborsVis[i][j - 1] >= 3) {
            canUp = false;
            canDown = false;
            canRight = false;
        }
    }
    if (j < n - 1) {
        neighborsVis[i][j + 1]++;
        if (!(vis & locBitRight) && neighborsVis[i][j + 1] >= 3) {
            canUp = false;
            canDown = false;
            canLeft = false;
        }
    }
    if (i > 0 && !(vis & locBitUp) && canUp) {
        visRow[i - 1]++;
        visCol[j]++;
        res += gen(i - 1, j, vis | locBitUp, visRow, visCol, neighborsVis, n);
        visRow[i - 1]--;
        visCol[j]--;
    }
    if (i < n - 1 && !(vis & locBitDown) && canDown) {
        visRow[i + 1]++;
        visCol[j]++;
        res += gen(i + 1, j, vis | locBitDown, visRow, visCol, neighborsVis, n);
        visRow[i + 1]--;
        visCol[j]--;
    }
    if (j > 0 && !(vis & locBitLeft) && canLeft) {
        visRow[i]++;
        visCol[j - 1]++;
        res += gen(i, j - 1, vis | locBitLeft, visRow, visCol, neighborsVis, n);
        visRow[i]--;
        visCol[j - 1]--;
    }
    if (j < n - 1 && !(vis & locBitRight) && canRight) {
        visRow[i]++;
        visCol[j + 1]++;
        res += gen(i, j + 1, vis | locBitRight, visRow, visCol, neighborsVis, n);
        visRow[i]--;
        visCol[j + 1]--;
    }
    if (i > 0) {
        neighborsVis[i - 1][j]--;
    }
    if (i < n - 1) {
        neighborsVis[i + 1][j]--;
    }
    if (j > 0) {
        neighborsVis[i][j - 1]--;
    }
    if (j < n - 1) {
        neighborsVis[i][j + 1]--;
    }
    return res;
}

int main() {
    ifstream fin("betsy.in");
    ofstream fout("betsy.out");
    int n;
    fin >> n;
    long long vis = 0;
    vis |= 1ULL << ((n - 1) * n);
    vector<int> visRow(n);
    vector<int> visCol(n);
    visRow[n - 1] = 1;
    visCol[0] = 1;
    vector<vector<int> > neighborsVis(n, vector<int>(n));
    fout << gen(n - 1, 0, vis, visRow, visCol, neighborsVis, n) << '\n';
    return 0;
}
