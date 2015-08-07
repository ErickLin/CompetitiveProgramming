/*
ID: Jugglebrosjr2
LANG: C++
TASK: twofive
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

//stores number of ways to fill the grid given a certain numByRow
long long dp[6][6][6][6][6];

long long numPos(vector<int> numByRow, vector<vector<char> > &grid, set<char> &rem) {
    long long* dpAt = &dp[numByRow[0]][numByRow[1]][numByRow[2]][numByRow[3]][numByRow[4]];
    if (*dpAt != -1) {
        return *dpAt;
    }
    long long ret = 0;
    char letter = *rem.begin();
    bool valid = true;
    for (int i = 0; i < 5 && valid; i++) {
        if (i == 0) {
            if (numByRow[i] < 5
                    && (numByRow[i] == 0 || letter > grid[i][numByRow[i] - 1])) {
                grid[i][numByRow[i]] = letter;
                numByRow[i]++;
                rem.erase(letter);
                ret += numPos(numByRow, grid, rem);
                rem.insert(letter);
                numByRow[i]--;
                grid[i][numByRow[i]] = ' ';
            }
        } else {
            if (numByRow[i] < numByRow[i - 1]
                    && (numByRow[i] == 0 || letter > grid[i][numByRow[i] - 1])
                    && letter > grid[i - 1][numByRow[i]]) {
                grid[i][numByRow[i]] = letter;
                numByRow[i]++;
                rem.erase(letter);
                ret += numPos(numByRow, grid, rem);
                rem.insert(letter);
                numByRow[i]--;
                grid[i][numByRow[i]] = ' ';
            }
        }
    }
    *dpAt = ret;
    return ret;
}

int main() {
    ifstream fin("twofive.in");
    ofstream fout("twofive.out");
    char task;
    fin >> task;
    long long m;
    string s;
    vector<vector<char> > grid(5, vector<char>(5));
    for (int i = 0; i < 5; i++) {
        fill(grid[i].begin(), grid[i].end(), ' ');
    }
    set<char> rem;
    for (char c = 'A'; c <= 'Z'; c++) {
        rem.insert(c);
    }
    if (task == 'N') {
        fin >> m;
        s = "";
        long long currentM = 1;
        for (int pos = 0; pos < 25; pos++) {
            char cAt = ' ';
            long long dM = 0;
            for (set<char>::iterator it = rem.begin(); it != rem.end(); it++) {
                if ((pos / 5 == 0 || *it > grid[pos / 5 - 1][pos % 5])
                        && (pos % 5 == 0 || *it > grid[pos / 5][pos % 5 - 1])) {
                    //initialize the letter that will potentially appear
                    if (cAt == ' ') {
                        cAt = *it;
                    }
                    //reset dp array for every new fixed set
                    memset(dp, -1, sizeof(dp[0][0][0][0][0]) * 6 * 6 * 6 * 6 * 6);
                    dp[5][5][5][5][5] = 1;
                    grid[pos / 5][pos % 5] = *it;
                    //used as dp state
                    vector<int> numByRow(5);
                    for (int i = 0; i < 5; i++) {
                        numByRow[i] = max(min(pos - i * 5 + 1, 5), 0);
                    }
                    set<char> remCopy = rem;
                    remCopy.erase(*it);
                    long long tempM = numPos(numByRow, grid, remCopy);
                    if (currentM + dM + tempM <= m) {
                        dM += tempM;
                        it++;
                        cAt = *it;
                        it--;
                    } else {
                        break;
                    }
                }
            }
            currentM += dM;
            grid[pos / 5][pos % 5] = cAt;
            rem.erase(cAt);
            s += cAt;
        }
        fout << s << '\n';
    } else {
        fin >> s;
        m = 1;
        for (int pos = 0; pos < 25; pos++) {
            for (set<char>::iterator it = rem.begin(); it != rem.end() && *it < s.at(pos); it++) {
                if ((pos / 5 == 0 || *it > grid[pos / 5 - 1][pos % 5])
                        && (pos % 5 == 0 || *it > grid[pos / 5][pos % 5 - 1])) {
                    //reset dp array for every new fixed set
                    memset(dp, -1, sizeof(dp[0][0][0][0][0]) * 6 * 6 * 6 * 6 * 6);
                    dp[5][5][5][5][5] = 1;
                    grid[pos / 5][pos % 5] = *it;
                    //used as dp state
                    vector<int> numByRow(5);
                    for (int i = 0; i < 5; i++) {
                        numByRow[i] = max(min(pos - i * 5 + 1, 5), 0);
                    }
                    set<char> remCopy = rem;
                    remCopy.erase(*it);
                    m += numPos(numByRow, grid, remCopy);
                }
            }
            grid[pos / 5][pos % 5] = s.at(pos);
            rem.erase(s.at(pos));
        }
        fout << m << '\n';
    }
    return 0;
}
