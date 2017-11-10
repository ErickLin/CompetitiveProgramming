#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
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
  string s;
  cin >> s;
  map<string, int> substr_to_freq;
  forf(i, s.size()) {
    for (int len = 1; i + len <= s.size(); len++) {
      substr_to_freq[s.substr(i, len)] = -1;
    }
  }
  for (const auto& kv : substr_to_freq) {
    string sub = kv.first;
    if (kv.second == -1) {
      substr_to_freq[sub] = 0;
      for (int i = 0; i < s.size(); ) {
        if (s.substr(i, sub.size()) == sub) {
          substr_to_freq[sub]++;
          i += sub.size();
        } else {
          i++;
        }
      }
    }
  }
  int min_len = s.size();
  for (const auto& kv : substr_to_freq) {
    int len = kv.first.size();
    int freq = kv.second;
    min_len = min(min_len, (int)(s.size() - freq * (len - 1) + len));
  }
  cout << min_len << '\n';
  return 0;
}
