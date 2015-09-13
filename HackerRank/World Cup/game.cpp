#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

void propagate(vector<long long> &w, vector<set<long long> > &edges, vector<long long> &dp
        , vector<long long> &parents, vector<bool> &visited, long long node) {
    dp[node] += w[node];
    for (set<long long>::iterator it = edges[node].begin(); it != edges[node].end(); it++) {
        if (!visited[*it]) {
            visited[*it] = true;
            parents[*it] = node;
            propagate(w, edges, dp, parents, visited, *it);
            dp[node] += dp[*it];
        }
    }
}

int main() {
    long long n;
    cin >> n;
    vector<long long> w(n);
    for (long long i = 0; i < n; i++) {
        cin >> w[i];
    }
    vector<set<long long> > edges(n);
    for (long long i = 0; i < n - 1; i++) {
        long long a, b;
        cin >> a >> b;
        a--;
        b--;
        edges[a].insert(b);
        edges[b].insert(a);
    }
    vector<long long> dp(n);
    fill(dp.begin(), dp.end(), 0);
    vector<bool> visited(n);
    visited[0] = true;
    vector<long long> parents(n);
    parents[0] = -1;
    //Let node 0 be the initial root
    propagate(w, edges, dp, parents, visited, 0);
    long long ans = 0;
    //Try using other nodes as root
    for (long long i = 0; i < n; i++) {
        long long maxSubtreeSize = 0;
        for (set<long long>::iterator it = edges[i].begin(); it != edges[i].end(); it++) {
            if (*it != parents[i] && dp[*it] > maxSubtreeSize) {
                maxSubtreeSize = dp[*it];
            }
        }
        maxSubtreeSize = max(maxSubtreeSize, dp[0] - dp[i]);
        //dp[0] is the total sum
        if (dp[0] - maxSubtreeSize > ans) {
            ans = dp[0] - maxSubtreeSize;
        }
    }
    cout << ans << '\n';
}
