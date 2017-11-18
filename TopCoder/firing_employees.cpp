#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef set<int> si;
typedef vector<vi> vvi;
typedef vector<si> vsi;
typedef vector<bool> vb;

class FiringEmployees {
  public:
    void calc_dp_profit(int cur, vi& dp_profit, vi& profit, vsi& subs) {
      dp_profit[cur] = profit[cur];
      for (int sub : subs[cur]) {
        calc_dp_profit(sub, dp_profit, profit, subs);
        dp_profit[cur] += dp_profit[sub];
      }
      dp_profit[cur] = max(dp_profit[cur], 0);
    }

    int fire(vi manager, vi salary, vi productivity) {
      int n = manager.size();
      vsi subs(n + 1);
      vi profit(n + 1);
      for (int i = 1; i <= n; i++) {
        subs[manager[i - 1]].insert(i);
        profit[i] = productivity[i - 1] - salary[i - 1];
      }
      vi dp_profit(n + 1);
      calc_dp_profit(0, dp_profit, profit, subs);
      return dp_profit[0];
    }
};

int main() {
  FiringEmployees a;
  cout << a.fire({0,0,0}, {1,2,3}, {3,2,1}) << '\n';
  cout << a.fire({0,1,2,3}, {4,3,2,1}, {2,3,4,5}) << '\n';
  cout << a.fire({0,1}, {1,10}, {5,5}) << '\n';
  cout << a.fire({0,1,2,1,2,3,4,2,3}, {5,3,6,8,4,2,4,6,7}, {2,5,7,8,5,3,5,7,9}) << '\n';
  cout << a.fire({0,0,1,1,2,2}, {1,1,1,2,2,2}, {2,2,2,1,1,1}) << '\n';
}
