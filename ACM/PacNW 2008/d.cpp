#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

vvi dist(126, vi(126));

struct Closer {
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) const {
        return dist[lhs.first][lhs.second] < dist[rhs.first][rhs.second];
    }
};

int main() {
    int n, t = 1;
    while ((cin >> n) && n) {
        vvi mat(n, vi(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> mat[i][j];
                dist[i][j] = 9 * n * n;
            }
        }
        /*
        vvi opt(n, vi(n));
        opt[0][0] = mat[0][0];
        for (int i = 1; i < n; i++) {
            opt[i][0] = opt[i - 1][0] + mat[i][0];
        }
        for (int j = 1; j < n; j++) {
            opt[0][j] = opt[0][j - 1] + mat[0][j];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                opt[i][j] = min(opt[i - 1][j], opt[i][j - 1]) + mat[i][j];
            }
        }
        */
        dist[0][0] = mat[0][0];
        priority_queue<pair<int, int>, vector<pair<int, int> >, Closer> q;
        vvb visited(n, vb(n));
        q.push(make_pair(0, 0));
        //while (!q.empty()) {
        for (int k = 0; k < n * n; k++) {
            int minDist = 9 * n * n, i, j;
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    if (dist[a][b] < minDist && !visited[a][b]) {
                        minDist = dist[a][b];
                        i = a;
                        j = b;
                    }
                }
            }
            /*
            pair<int, int> cur = q.top();
            q.pop();
            int i = cur.first;
            int j = cur.second;
            */
            if (!visited[i][j]) {
                if (i > 0 && dist[i][j] + mat[i - 1][j] < dist[i - 1][j]) {
                    dist[i - 1][j] = dist[i][j] + mat[i - 1][j];
                    q.push(make_pair(i - 1, j));
                }
                if (i < n - 1 && dist[i][j] + mat[i + 1][j] < dist[i + 1][j]) {
                    dist[i + 1][j] = dist[i][j] + mat[i + 1][j];
                    q.push(make_pair(i + 1, j));
                }
                if (j > 0 && dist[i][j] + mat[i][j - 1] < dist[i][j - 1]) {
                    dist[i][j - 1] = dist[i][j] + mat[i][j - 1];
                    q.push(make_pair(i, j - 1));
                }
                if (j < n - 1 && dist[i][j] + mat[i][j + 1] < dist[i][j + 1]) {
                    dist[i][j + 1] = dist[i][j] + mat[i][j + 1];
                    q.push(make_pair(i, j + 1));
                }
                visited[i][j] = true;
            }
        }
        cout << "Problem " << t << ": " << dist[n - 1][n - 1] << '\n';
        t++;
    }
    return 0;
}
