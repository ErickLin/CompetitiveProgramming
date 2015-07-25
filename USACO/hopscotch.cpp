/*
ID: Jugglebrosjr2
LANG: C++
TASK: hopscotch
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
long MOD = 1000000007;

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
    //freopen("hopscotch.in", "r", stdin);
    //freopen("hopscotch.out", "w", stdout);
    ifstream fin("hopscotch.in");
    ofstream fout("hopscotch.out");
    /*
    fout << "750 750 562500\n";
    for (int i = 0; i < 750; i++) {
    	for (int j = 0; j < 750; j++) {
    		fout << rand() % 562500 << " ";
    	}
    	fout << '\n';
    }
    */
    unsigned int r, c, k;
    fin >> r >> c >> k;
    vector<vector<int> > grid(r, vector<int>(c));
    for (int i = 0; i < r; i++) {
    	for (int j = 0; j < c; j++) {
    		fin >> grid[i][j];
    	}
    }
    vector<pair<int, int> > q((r - 2) * (c - 2) + 1);
    q[0] = make_pair(0, 0);
    int pos = 1;
    for (int diag = 2; diag <= (r - 2) + (c - 2); diag++) {
    	int startRow = 1;
    	if (diag > (2 + (r - 2) + (c - 2)) / 2) {
    		startRow = diag - (2 + (r - 2) + (c - 2)) / 2 + 1;
    	}
    	for (int row = startRow; row <= diag - 1 && row <= r - 2; row++) {
    		int col = diag - row;
    		q[pos++] = make_pair(row, col);
    	}
    }
    vector<vector<int> > dp(r, vector<int>(c));
    dp[0][0] = 1;
    for (int i = 0; i < q.size(); i++) {
    	//fout << q[i].first << " " << q[i].second << '\n';
    	for (int row = q[i].first + 1; row <= r - 2; row++) {
    		for (int col = q[i].second + 1; col <= c - 2; col++) {
    			if (grid[q[i].first][q[i].second] != grid[row][col]) {
    				dp[row][col] = (dp[row][col] + dp[q[i].first][q[i].second]) % MOD;
    			}
    		}
    	}
    	if (grid[q[i].first][q[i].second] != grid[r - 1][c - 1]) {
    		dp[r - 1][c - 1] = (dp[r - 1][c - 1] + dp[q[i].first][q[i].second]) % MOD;
    	}
    }
    fout << dp[r - 1][c - 1] << '\n';
    return 0;
}