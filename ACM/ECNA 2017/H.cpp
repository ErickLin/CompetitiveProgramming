#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;

int main() {
  int n, m;
  cin >> n >> m;
  vvb pic(n, vb(m));
  forf(i, n) {
    forf(j, m) {
      char c;
      cin >> c;
      if (c == '#') {
        pic[i][j] = 1;
      }
    }
  }
  vvi labeled_pic(n, vi(m));
  vvb vis(n, vb(m));
  int count = 0;
  forf(i, n) {
    forf(j, m) {
      if (!vis[i][j] && pic[i][j]) {
        labeled_pic[i][j] = ++count;
        vis[i][j] = true;
        stack<pii> s;
        s.push(mp(i, j));
        while (!s.empty()) {
          int y = s.top().first;
          int x = s.top().second;
          s.pop();
          vpii neighbors({mp(y - 1, x - 1), mp(y - 1, x), mp(y - 1, x + 1), mp(y, x - 1), mp(y, x + 1), mp(y + 1, x - 1), mp(y + 1, x), mp(y + 1, x + 1)});
          for (pii next : neighbors) {
            int y2 = next.first, x2 = next.second;
            if (y2 >= 0 && y2 < n && x2 >= 0 && x2 < m && !vis[y2][x2] && pic[y2][x2]) {
              labeled_pic[y2][x2] = count;
              vis[y2][x2] = true;
              s.push(mp(y2, x2));
            }
          }
        }
      }
    }
  }
  cout << count << '\n';
  /*
  forf(i, n) {
    forf(j, m) {
      cout << labeled_pic[i][j];
    }
    cout << '\n';
  }
  */
}
