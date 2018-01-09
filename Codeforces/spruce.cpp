// 913B
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef vector<int> vi;
typedef vector<bool> vb;
typedef set<int> si;
typedef vector<si> vsi;

int main() {
  int n; cin >> n;
  vi par(n);
  par[0] = -1;
  vsi children(n);
  forf3(i, n - 1) {
    int p; cin >> p; p--;
    par[i] = p;
    children[p].insert(i);
  }
  vb is_leaf(n);
  vi num_leaf_children(n);
  forf(i, n) {
    if (children[i].empty()) {
      is_leaf[i] = true;
      num_leaf_children[par[i]]++;
    }
  }
  forf(i, n) {
    if (!is_leaf[i] && num_leaf_children[i] < 3) {
      cout << "No\n";
      return 0;
    }
  }
  cout << "Yes\n";
}
