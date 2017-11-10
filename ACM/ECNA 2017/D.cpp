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
  int n, k;
  cin >> n >> k;
  deque<int> cmds;
  forf(i, k) {
    string s;
    cin >> s;
    if (s == "undo") {
      int m;
      cin >> m;
      forf(j, m) {
        cmds.pop_back();
      }
    } else {
      int p = stoi(s);
      cmds.push_back(p);
    }
  }
  int cur = 0;
  while (!cmds.empty()) {
    cur = (cur + cmds.front()) % n;
    cmds.pop_front();
    while (cur < 0) {
      cur += n;
    }
  }
  cout << cur << '\n';
}
