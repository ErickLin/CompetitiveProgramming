// 913D
#include <iostream>
#include <vector>
using namespace std;
#define mp make_pair
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

typedef pair<int, pair<int, int>> problem;
int main() {
  int n, T; cin >> n >> T;
  vector<problem> p(n);
  forf(i, n) {
    int a, t; cin >> a >> t;
    p[i] = mp(t, mp(a, i));
  }
  sort(p.begin(), p.end());

  int cumul_t = 0, s = 0, best_s = 0;
  set<int> sol_idxes, ins_sol_idxes, del_sol_idxes;
  map<int, vi> used_a_to_sol_idxes;
  forf(i, n) {
    if (cumul_t + p[i].first > T) {
      break;
    }
    if (k < p[i].second.first) {
      //cout << p[i].first << ' ' << p[i].second.first << '\n';
      cumul_t += p[i].first;
      s++;
      ins_sol_idxes.insert(i);
      used_a_to_sol_idxes[p[i].second.first].pb(i);
      auto it = used_a_to_sol_idxes.begin();
      if (it->first < k) {
        s -= it->second.size();
        for (int idx : it->second) {
          cumul_t -= p[idx].second.first;
          del_sol_idxes.insert(idx);
        }
        used_a_to_sol_idxes.erase(it);
      }
      /*
      for (const auto& kv : used_a_to_sol_idxes) {
        cout << kv.first << ' ';
      }
      cout << '\n';
      */
    }
    if (s > best_s) {
      best_s = s;
      for (int idx : ins_sol_idxes) {
        sol_idxes.insert(idx);
      }
      ins_sol_idxes.clear();
      for (int idx : del_sol_idxes) {
        sol_idxes.erase(idx);
      }
      del_sol_idxes.clear();
    }
  }

  cout << s << '\n' << s << '\n';
  for (int idx : sol_idxes) {
    cout << p[idx].second.second + 1 << ' ';
  }
  cout << '\n';
}
