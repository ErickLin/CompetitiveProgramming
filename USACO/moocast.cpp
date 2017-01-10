/*
ID: Jugglebrosjr2
LANG: C++
TASK: moocast
*/
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");
    int n;
    fin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        fin >> x[i] >> y[i];
    }
    vector<vector<int> > d(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
            //cout << "d[" << i << "][" << j << "] = " << d[i][j] << '\n';
        }
    }
    int lo = 1, hi = INT_MAX;
    int ans = INT_MAX;
    int mid = lo + (hi - lo)/2;
    while (lo <= hi) {
        int mid = lo + (hi - lo)/2;
        stack<int> stk;
        vector<bool> visited(n);
        stk.push(0);
        visited[0] = true;
        int count = 1;
        while (!stk.empty()) {
            int cur = stk.top();
            stk.pop();
            for (int next = 0; next < n; next++) {
                if (!visited[next] && d[cur][next] <= mid) {
                    stk.push(next);
                    visited[next] = true;
                    count++;
                }
            }
        }
        if (count == n) {
            hi = mid - 1;
            ans = min(ans, mid);
        } else {
            lo = mid + 1;
        }
    }
    fout << ans << '\n';
    return 0;
}
