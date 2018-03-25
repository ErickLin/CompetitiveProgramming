#include <vector>
using namespace std;
typedef long long ll;

// sum of elements in [0, idx]
ll sum(vector<int>& bit, int idx) {
  ll ret = 0;
  while (idx > 0) {
    ret += bit[idx];
    idx -= idx & (-idx);
  }
  return ret;
}

void update(vector<int>& bit, int idx, int val) {
  while (idx < bit.size()) {
    bit[idx] += val;
    idx += idx & (-idx);
  }
}
