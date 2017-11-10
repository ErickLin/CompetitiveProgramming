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
  string msg;
  cin >> msg;
  for (short half = 0; half <= 1; half++) {
    int rot_val = 0;
    for (int i = half * msg.size() / 2; i < (half + 1) * msg.size() / 2; i++) {
      rot_val = (rot_val + msg[i] - 'A') % 26;
    }
    for (int i = half * msg.size() / 2; i < (half + 1) * msg.size() / 2; i++) {
      msg[i] += rot_val;
      if (msg[i] > 'Z') {
        msg[i] -= 26;
      }
    }
  }
  for (int i = 0; i < msg.size() / 2; i++) {
    msg[i] += msg[msg.size() / 2 + i] - 'A';
    if (msg[i] > 'Z') {
      msg[i] -= 26;
    }
  }
  cout << msg.substr(0, msg.size() / 2) << '\n';
}
