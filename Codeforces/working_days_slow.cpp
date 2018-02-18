// 915E
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef set<int> si;
typedef map<int, int> mii;

/*
int smallest_overlapping(int l, int r, vii& intervals) {
  int lo = 0, hi = intervals.size() - 1;
  int ans = INT_MAX;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (intervals[mid].second >= l) {
      ans = min(ans, mid);
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return ans;
}
*/

int main() {
  int n, q;
  cin >> n >> q;
  si rs = {n};
  mii r_to_l;
  r_to_l[n] = 1;
  int num_working_days = n;
  forf(i, q) {
    int l, r, k;
    cin >> l >> r >> k;
    int max_r = r, min_l = l;
    for (auto it = rs.lower_bound(l - 1); it != rs.end(); it = rs.erase(it)) {
      int other_r = *it, other_l = r_to_l[other_r];
      if (other_l > r + 1) break;
      max_r = max(max_r, other_r);
      min_l = min(min_l, other_l);
      num_working_days -= other_r - other_l + 1;
      r_to_l.erase(other_r);
    }
    if (k == 1) {
      if (min_l < l) {
        num_working_days += l - min_l;
        rs.insert(l - 1);
        r_to_l[l - 1] = min_l;
      }
      if (max_r > r) {
        num_working_days += max_r - r;
        rs.insert(max_r);
        r_to_l[max_r] = r + 1;
      }
    } else {
      num_working_days += max_r - min_l + 1;
      rs.insert(max_r);
      r_to_l[max_r] = min_l;
    }
    /*
    cout << "intervals: ";
    for (int r : rs) {
      cout << '[' << r_to_l[r] << ", " << r << "], ";
    }
    */
    cout << num_working_days << '\n';
  }
}
