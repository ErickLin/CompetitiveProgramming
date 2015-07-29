/*
ID: Jugglebrosjr2
LANG: C++
TASK: snail
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool outOfBounds(int r, int c, int n) {
    if (r >= n || r < 0 || c >= n || c < 0) {
        return true;
    }
    return false;
}

int travel(int r, int c, int dr, int dc, vector<vector<bool> > &visited
        , int numSquares, vector<vector<bool> > &hasBarrier) {
    int n = hasBarrier.size(), rStart = r, cStart = c;
    while (outOfBounds(r + dr, c + dc, n) || !visited[r + dr][c + dc]) {
        //cout << r << ' ' << c << ' ' << dr << ' ' << dc << ' ' << numSquares << '\n';
        if (outOfBounds(r + dr, c + dc, n)
                || hasBarrier[r + dr][c + dc]) {
            int ans = numSquares;
            if (dr == 0) {
                if (!outOfBounds(r + 1, c, n)
                        && !visited[r + 1][c] && !hasBarrier[r + 1][c])
                    ans = max(ans, travel(r, c, 1, 0, visited, numSquares, hasBarrier));
                if (!outOfBounds(r - 1, c, n)
                        && !visited[r - 1][c] && !hasBarrier[r - 1][c])
                    ans = max(ans, travel(r, c, -1, 0, visited, numSquares, hasBarrier));
            } else {
                if (!outOfBounds(r, c + 1, n)
                        && !visited[r][c + 1] && !hasBarrier[r][c + 1])
                    ans = max(ans, travel(r, c, 0, 1, visited, numSquares, hasBarrier));
                if (!outOfBounds(r, c - 1, n)
                        && !visited[r][c - 1] && !hasBarrier[r][c - 1])
                    ans = max(ans, travel(r, c, 0, -1, visited, numSquares, hasBarrier));
            }
            int tempR = r, tempC = c;
            while (tempR != rStart || tempC != cStart) {
                visited[tempR][tempC] = false;
                tempR -= dr;
                tempC -= dc;
            }
            return ans;
        } else {
            r += dr;
            c += dc;
            visited[r][c] = true;
            numSquares++;
        }
    }
    int tempR = r, tempC = c;
    while (tempR != rStart || tempC != cStart) {
        visited[tempR][tempC] = false;
        tempR -= dr;
        tempC -= dc;
    }
    return numSquares;
}

int main() {
    ifstream fin("snail.in");
    ofstream fout("snail.out");
    int n, b;
    fin >> n >> b;
    vector<vector<int> > rPlus(n, vector<int>(n));
    vector<vector<int> > rMinus(n, vector<int>(n));
    vector<vector<int> > cPlus(n, vector<int>(n));
    vector<vector<int> > cMinus(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rPlus[i][j] = n - 1;
            rMinus[i][j] = 0;
            cPlus[i][j] = n - 1;
            cMinus[i][j] = 0;
        }
    }
    vector<vector<bool> > hasBarrier(n, vector<bool>(n));
    for (int i = 0; i < b; i++) {
        char dim1;
        int dim2;
        fin >> dim1 >> dim2;
        hasBarrier[dim1 - 'A'][dim2 - 1] = true;
    }
    vector<vector<bool> > visited(n, vector<bool>(n));
    visited[0][0] = true;
    fout << max(travel(0, 0, 1, 0, visited, 1, hasBarrier)
            , travel(0, 0, 0, 1, visited, 1, hasBarrier)) << '\n';
    return 0;
}
