#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define mp make_pair
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef pair<int, int> ii;
typedef map<int, int> mii;
typedef vector<int> vi;
typedef vector<bool> vb;
 
bool can_reach(int cur, int d, int badge_num, vb& vis,
               vector<map<int, ii>>& doors) {
  if (cur == d) return true;
  for (const auto& kv : doors[cur]) {
    int next = kv.first;
    if (vis[next]) continue;
    ii range = kv.second;
    if (badge_num >= range.first && badge_num <= range.second) {
      vis[next] = true;
      bool can_reach_next = can_reach(next, d, badge_num, vis, doors);
      if (can_reach_next) return true;
    }
  }
  return false;
}
 
int main() {
  int n, m, k, s, d;
  cin >> n >> m >> k >> s >> d;
	s--;
  d--;
  vector<map<int, ii>> doors(n);
  set<int> endpts, left_endpts, right_endpts;
  forf(i, m) {
    int a, b, l, r;
    cin >> a >> b >> l >> r;
    a--;
    b--;
    doors[a][b] = mp(l, r);
    endpts.insert(l);
    endpts.insert(r);
    left_endpts.insert(l);
    right_endpts.insert(r);
  }
  vi endpts_vec(endpts.begin(), endpts.end());
  int ans = 0;
  int earliest_valid_left_endpt = -1;
  for (int endpt : endpts_vec) {
    {
      vb vis(n);
      vis[s] = true;
      if (left_endpts.count(endpt) && earliest_valid_left_endpt == -1 &&
          can_reach(s, d, endpt, vis, doors)) {
        earliest_valid_left_endpt = endpt;
      }
    }
    {
      vb vis(n);
      vis[s] = true;
      if (right_endpts.count(endpt) && earliest_valid_left_endpt != -1 &&
          !can_reach(s, d, endpt + 1, vis, doors)) {
        ans += endpt - earliest_valid_left_endpt + 1;
        earliest_valid_left_endpt = -1;
      }
    }
  }
  cout << ans << '\n';
}
